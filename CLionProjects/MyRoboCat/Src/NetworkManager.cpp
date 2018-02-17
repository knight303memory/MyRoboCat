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
    float time =
}



