//
// Created by Killua on 2018/2/10.
//

#include "MyRoboCatPCH.h"


std::unique_ptr<NetworkManager> NetworkManager::sInstance;

namespace {
    const float kTimeBetweenHellos = 1.f;
    const float kStartDelay = 3.0f;
    const int kSubTurnsPerTurn = 3;
    const int kMaxPlayerCount = 4;
}


bool NetworkManager::StaticInitAsMasterPeer(uint16_t inPort, const std::string &inName) {

    sInstance = std::unique_ptr<NetworkManager>(new NetworkManager());

    return sInstance->InitAsMasterPeer(inPort, inName);

}

bool NetworkManager::StaticInitAsPeer(const SocketAddress &inMPAddress, const std::string &inName) {
    sInstance = std::unique_ptr<NetworkManager>(new NetworkManager());

    return sInstance->InitAsPeer(inMPAddress, inName);
}

NetworkManager::NetworkManager() : mBytesSentThisFrame(0), mDropPacketChance(0.f), mSimulatedLatency(0.f),
                                   mBytesReceivedPerSecond(), mBytesSentPerSecond(),
                                   mPlayerId(0), mNewNetworkId(1), mIsMasterPeer(false), mState(NMS_UNITIALIZED),
                                   mPlayerCount(0), mHightestPlayerId(0), mTimeOfLastHello(0.0f), mTimeToStart(-1.0f),
                                   mTurnNumber(-2), mSubTurnNumber(0) {

    mTurnData.resize(100000);

}

NetworkManager::~NetworkManager() {}

bool NetworkManager::InitAsMasterPeer(uint16_t inPort, const string &inName) {
    if (!InitSocket(inPort)) {
        return false;
    }

    mPlayerId = 1;
    mHightestPlayerId = mPlayerId;
    mIsMasterPeer = true;
    mPlayerCount = 1;

    mState = NMS_LOBBY;
    mName = inName;
    mPlayerNameMap.emplace(mPlayerId, mName);

    return true;
}

bool NetworkManager::InitAsPeer(const SocketAddress &inMPAddress, const string &inName) {
    if (!InitSocket(0)) {
        return false;
    }

    mMasterPeerAddr = inMPAddress;
    mState = NMS_HELLO;

    mName = inName;

    return true;
}


bool NetworkManager::InitSocket(uint16_t inPort) {

    mSocket = SocketUtil::CreateUDPSocket(INET);

    SocketAddress ownAddress(INADDR_ANY, inPort);

    mSocket->Bind(ownAddress);

    printf("Initializing NetworkManger at port %d", inPort);

    if (mSocket == nullptr) {
        return false;
    }

    if (mSocket->SetNonBlockingMode(true) != NO_ERROR) {
        return false;
    }

    return true;
}

void NetworkManager::ProcessIncomingPackets() {
    ReadIncomingPacketsIntoQueue();

    ProcessQueuePackets();

    UpdateBytesSentLastFrame();

}


void NetworkManager::SendOutgoingPackets() {
    switch (mState) {
        case NMS_HELLO:
            UpdateSayingHello();
            break;
        case NMS_STARTING:
            UpdateStarting();
            break;
        case NMS_PLAYING:
            UpdateSendTurnPacket();
            break;
        default:
            break;
    }
}

void NetworkManager::UpdateSayingHello(bool inForce) {
    float time = Timing::sInstance.GetTimeF();

    if (inForce || time > mTimeOfLastHello + kTimeBetweenHellos) {
        SendHelloPacket();
        mTimeOfLastHello = time;
    }
}

void NetworkManager::SendHelloPacket() {
    OutputMemoryBitStream helloPacket;

    helloPacket.Write(kHelloCC);
    helloPacket.Write(mName);
    SendPacket(helloPacket, mMasterPeerAddr);
}


void NetworkManager::UpdateStarting() {
    mTimeToStart -= Timing::sInstance.GetDeltaTime();

    if (mTimeToStart <= 0.0f) {
        EnterPlayingState();
    }
}


void NetworkManager::UpdateSendTurnPacket() {
    mSubTurnNumber++;
    if (mSubTurnNumber == kSubTurnsPerTurn) {
        TurnData data(mPlayerId, RandGen::sInstance->GetRandomUInt32(0, UINT32_MAX), ComputerGlobalCRC(),
                      InputManager::sInstance->GetCommandList());

        OutputMemoryBitStream packet;
        packet.Write(kTurnCC);
        packet.Write(mTurnNumber + 2);
        packet.Write(mPlayerId);
        data.Write(packet);

        for (auto &iter : mPlayerToSocketMap) {
            SendPacket(packet, iter.second);
        }

        mTurnData[mTurnNumber + 2].emplace(mPlayerId, data);
        InputManager::sInstance->ClearCommandList();

        if (mTurnNumber >= 0) {
            TryAdvanceTurn();
        } else {
            mTurnNumber++;
            mSubTurnNumber = 0;
        }

    }
}


void NetworkManager::TryAdvanceTurn() {
    if (mTurnData[mTurnNumber + 1].size() == mPlayerCount) {
        if (mState == NMS_DELAY) {
            InputManager::sInstance->ClearCommandList();
            mState = NMS_PLAYING;
            SDL_Delay(100);
        }

        mTurnNumber++;
        mSubTurnNumber = 0;

        if (CheckSync(mTurnData[mTurnNumber])) {
            for (auto &iter : mTurnData[mTurnNumber]) {
                iter.second.GetCommandList().ProcessCommands(iter.first);
            }
        } else {
            printf("DESYNC: Game Over man , game over");
            Engine::sInstance->SetShouldKeepingRunning(false);
        }
    } else {
        mState = NMS_DELAY;
    }
}

void NetworkManager::ProcessPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    switch (mState) {
        case NMS_HELLO:
            ProcessPacketsHello(inInputStream, inFromAddress);
            break;
        case NMS_LOBBY:
            ProcessPacketsLobby(inInputStream, inFromAddress);
            break;
        case NMS_PLAYING:
            ProcessPacketsPlaying(inInputStream, inFromAddress);
            break;
        case NMS_DELAY:
            ProcessPacketsDelay(inInputStream, inFromAddress);
            break;
        default:
            break;
    }
}


//processHello
void NetworkManager::ProcessPacketsHello(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    uint32_t packetType;
    inInputStream.Read(packetType);

    switch (packetType) {
        case kNotMasterPeerCC:
            HandleNotMPPacket(inInputStream);
            break;
        case kWelcomeCC:
            HandleWelcomePacket(inInputStream);
            break;
        case kNotJoinableCC:
        default:
            printf("failed to join game!\n");
            Engine::sInstance->SetShouldKeepingRunning(false);
            break;
    }

}


void NetworkManager::HandleNotMPPacket(InputMemoryBitStream &inInputStream) {
    mMasterPeerAddr.Read(inInputStream);
    UpdateSayingHello(true);
}

void NetworkManager::HandleWelcomePacket(InputMemoryBitStream &inInputStream) {
    //我的playerid
    int playerId;

    inInputStream.Read(playerId);

    UpdateHigestPlayerId(playerId);
    mPlayerId = playerId;

    mPlayerNameMap.emplace(mPlayerId, mName);

    //master playerid
    inInputStream.Read(playerId);
    UpdateHigestPlayerId(playerId);
    mPlayerToSocketMap.emplace(playerId, mMasterPeerAddr);
    mSocketToPlayerMap.emplace(mMasterPeerAddr, mPlayerId);


    //其他的player
    inInputStream.Read(mPlayerCount);
    SocketAddress socketAddr;

    for (int i = 0; i < mPlayerCount - 1; ++i) {
        inInputStream.Read(playerId);
        UpdateHigestPlayerId(playerId);
        socketAddr.Read(inInputStream);
        mPlayerToSocketMap.emplace(playerId, socketAddr);
        mSocketToPlayerMap.emplace(socketAddr, playerId);
    }

    std::string name;
    for (int i = 0; i < mPlayerCount; ++i) {
        inInputStream.Read(playerId);
        inInputStream.Read(name);
        mPlayerNameMap.emplace(playerId, name);
    }

    mPlayerCount++;

    OutputMemoryBitStream outPacket;
    outPacket.Write(kInttroCC);
    outPacket.Write(mPlayerId);
    outPacket.Write(mName);

    for (auto &iter : mPlayerToSocketMap) {
        SendPacket(outPacket, iter.second);
    }

    mState = NMS_LOBBY;
}

//ProcessPacketsLobby
void NetworkManager::ProcessPacketsLobby(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    uint32_t packetType;
    inInputStream.Read(packetType);

    switch (packetType) {
        case kHelloCC:
            HandleHelloPacket(inInputStream, inFromAddress);
            break;
        case kInttroCC:
            HandleIntroPacket(inInputStream, inFromAddress);
            break;
        case kStartCC:
            HandleStartPacket(inInputStream, inFromAddress);
            break;
        default:
            printf("Unexpected packet received in Lobby state");
            break;
    }
}


void NetworkManager::HandleHelloPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    if (mSocketToPlayerMap.find(inFromAddress) != mSocketToPlayerMap.end()) {
        return;
    }

    if (mPlayerCount >= kMaxPlayerCount) {
        OutputMemoryBitStream outPacket;
        outPacket.Write(kNotJoinableCC);
        SendPacket(outPacket, inFromAddress);
        return;
    }

    if (mIsMasterPeer) {
        std::string name;
        inInputStream.Read(name);

        OutputMemoryBitStream outputStream;
        outputStream.Write(kWelcomeCC);

        mHightestPlayerId++;
        outputStream.Write(mHightestPlayerId);

        outputStream.Write(mPlayerId);
        outputStream.Write(mPlayerCount);

        for (auto &iter : mPlayerToSocketMap) {
            outputStream.Write(iter.first);
            iter.second.Write(outputStream);
        }

        for (auto &iter : mPlayerNameMap) {
            outputStream.Write(iter.first);
            outputStream.Write(iter.second);
        }

        SendPacket(outputStream, inFromAddress);

        mPlayerCount++;
        mPlayerToSocketMap.emplace(mHightestPlayerId, inFromAddress);
        mSocketToPlayerMap.emplace(inFromAddress, mHightestPlayerId);
        mPlayerNameMap.emplace(mHightestPlayerId, name);

    } else {
        OutputMemoryBitStream outPacket;
        outPacket.Write(kNotMasterPeerCC);
        mMasterPeerAddr.Write(outPacket);
        SendPacket(outPacket, inFromAddress);
    }

}

void NetworkManager::HandleIntroPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    if (!mIsMasterPeer) {
        int playerId;
        string name;

        inInputStream.Read(playerId);
        inInputStream.Read(name);

        UpdateHigestPlayerId(playerId);
        mPlayerCount++;

        mPlayerToSocketMap.emplace(playerId, inFromAddress);
        mSocketToPlayerMap.emplace(inFromAddress, playerId);
        mPlayerNameMap.emplace(playerId, name);

    }
}

void NetworkManager::HandleStartPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    if (inFromAddress == mMasterPeerAddr) {
        printf("get order to go\n");

        uint32_t seed;
        inInputStream.Read(seed);
        RandGen::sInstance->Seed(seed);

        mState = NMS_STARTING;
        mTimeToStart = kStartDelay - Timing::sInstance.GetDeltaTime();

    }
}

//ProcessPacketsPlaying
void NetworkManager::ProcessPacketsPlaying(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    uint32_t packetType;
    inInputStream.Read(packetType);

    switch (packetType) {
        case kTurnCC:
            HandleTurnPacket(inInputStream, inFromAddress);
            break;
        default:
            break;
    }
}


void NetworkManager::HandleTurnPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    if (mSocketToPlayerMap.find(inFromAddress) != mSocketToPlayerMap.end()) {
        int expectedId = mSocketToPlayerMap[inFromAddress];

        int turnNum;
        int playerId;

        inInputStream.Read(turnNum);
        inInputStream.Read(playerId);

        if (playerId != expectedId) {
            printf("we received turn data for different player id!\n");
            return;
        }

        TurnData data;
        data.Read(inInputStream);

        mTurnData[turnNum].emplace(mPlayerId, data);

    }
}

//process delay
void NetworkManager::ProcessPacketsDelay(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress) {
    uint32_t packetType;
    inInputStream.Read(packetType);

    if (packetType == kTurnCC) {
        HandleTurnPacket(inInputStream, inFromAddress);
        TryAdvanceTurn();
    }

}

void NetworkManager::HandleConnectionReset(const SocketAddress &inFromAddress) {
    if (mSocketToPlayerMap.find(inFromAddress) != mSocketToPlayerMap.end()) {
        uint32_t playerId = mSocketToPlayerMap[inFromAddress];
        mSocketToPlayerMap.erase(inFromAddress);
        mPlayerToSocketMap.erase(playerId);
        mPlayerNameMap.erase(playerId);

        ScoreBoardManager::sInstance->RemoveEntry(playerId);
        mPlayerCount--;

        if (inFromAddress == mMasterPeerAddr) {
            
        }
    }
}
