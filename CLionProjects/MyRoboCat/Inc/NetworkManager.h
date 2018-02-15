//
// Created by Killua on 2018/2/10.
//

#ifndef MYROBOCAT_NETWORKMANAGER_H
#define MYROBOCAT_NETWORKMANAGER_H


#include <cstdint>
#include <memory>
#include <map>
#include <unordered_map>
#include <queue>
#include "SocketAddress.h"
#include "GameObject.h"
#include "UDPSocket.h"
#include <string>

class NetworkManager {
public:
    static const uint32_t kHelloCC = 'HELO';
    static const uint32_t kWelcomeCC = 'WLCM';
    static const uint32_t kNotMasterPeerCC = 'NOMP';
    static const uint32_t kNotJoinableCC = 'NOJN';
    static const uint32_t kInttroCC = 'INTR';
    static const uint32_t kTurnCC = 'TURN';
    static const uint32_t kStartCC = 'STRT';
    static const int kMaxPacketPerFrameCount = 10;

    enum NetworkManagerState {
        NMS_UNITIALIZED,
        NMS_HELLO,
        NMS_LOBBY,
        NMS_STARTING,
        NMS_PLAYING,
        NMS_DELAY
    };

    static std::unique_ptr<NetworkManager> sInstance;

    static bool StaticInitAsMasterPeer(uint16_t inPort, const std::string &inName);

    static bool StaticInitAsPeer(const SocketAddress &inMPAddress, const std::string &inName);

    NetworkManager();

    ~NetworkManager();

    void ProcessIncomingPackets();

    void SendOutgoingPackets();

    void ProcessPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

private:

    void UpdateSayingHello(bool inForce = false);

    void SendHelloPacket();

    void UpdateStarting();

    void UpdateSendTurnPacket();

    void TryAdvanceTurn();

private:
    void ProcessPacketsHello(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void HandleNotMPPacket(InputMemoryBitStream &inInputStream);

    void HandleWelcomePacket(InputMemoryBitStream &inInputStream);

    void ProcessPacketsLobby(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void HandleHelloPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void HandleIntroPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void HandleStartPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void ProcessPacketsPlaying(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void HandleTurnPacket(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

    void ProcessPacketsDelay(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);

public:
    void HandleConnectionReset(const SocketAddress &inFromAddress);

    void SendPacket(const OutputMemoryBitStream &inOutputStream, const SocketAddress &inToAddress);

    void TryStartGame();

    const WeightedTimedMovingAverage &GetBytesReceivedPerSecond() const { return }

    const WeightedTimedMovingAverage &GetBytesSentPerSecond() const {

    }

    void SetDropPacketChance(float inChance) {
        //todo
    }

    float GetDropPacketChance() const {
        //todo
    }

    void SetSimulatedLatency(float inLatency) {
        //todo
    }

    void GetSimulatedLatency() const {
        //todo
    }

    bool IsMaterPeer() const {
        //todo
    }

    float GetTimeToStart() const {
        //todo
    }

    GameObjectPtr GetGameObject(uint32_t inNetworkId) const;

    GameObjectPtr RegisterAndReturn(GameObject *inGameObject);

    void UnregisterGameObject(GameObject *inGameObject);

    NetworkManagerState GetState() const {
        return mState;
    }

    int GetPlayerCount() const {
        return mPlayerCount;
    }

    int GetTurnNumber() const {
        return mTurnNumber;
    }

    int GetSubTurnNumber() const {
        return mSubTurnNumber;
    }

    uint32_t GetMyPlayerId() const {
        return mPlayerId;
    }

private:
    void AddToNetworkIdToGameObjectMap(GameObjectPtr inGameObject);

    void RemoveFromNetworkIdToGameObjectMap(GameObjectPtr inGameObject);

    void RegisterGameObject(GameObjectPtr inGameObject);

    uint32_t GetNewNetworkId();

    uint32_t ComputerGlobalCRC();

    bool InitAsMasterPeer(uint16_t inPort, const string &inName);

    bool InitAsPeer(const SocketAddress &inMPAddress, const string &inName);

    bool InitSocket(uint16_t inPort);


    class ReceivedPacket {
    public:
        ReceivedPacket(float inReceivedTime, InputMemoryBitStream &inInputMemoryBitStream,
                       const SocketAddress &inAddress);

        const SocketAddress &GetFromAddress() const { mReceivedTime; }

        float GetReceivedTime() const {
            return mReceivedTime;
        }


        InputMemoryBitStream &GetPacketBuffer() {
            return mPacketBuffer;
        }

    private:
        float mReceivedTime;
        InputMemoryBitStream mPacketBuffer;
        SocketAddress mFromAddress;

    };

    void UpdateBytesSentLastFrame();

    void ReadIncomingPacketsIntoQueue();

    void ProcessQueuePackets();

    void UpdateHigestPlayerId(uint32_t inId);

    void EnterPlayingState();

    void SpawnCat(uint32_t inPlayerId, const Vector3 &inSpawnVec);

    typedef std::map<uint32_t, SocketAddress> IntToSocketAddrMap;
    typedef std::map<uint32_t, string> IntToStrMap;
    typedef std::map<uint32_t, TurnData> IntToTurnDataMap;
    typedef std::map<uint32_t, GameObjectPtr> IntToGameObjectMap;
    typedef std::map<uint32_t, GameObjectPtr> IntToGameObjectMap;
    typedef std::unordered_map<SocketAddress, uint32_t> SocketAddrToIntMap;

    bool CheckSync(IntToTurnDataMap &inTurnMap);

    std::queue<ReceivedPacket, std:: < ReceivedPacket>> mPacketQueue;
    IntToGameObjectMap mNetworkIdToGameObjectMap;
    IntToSocketAddrMap mPlayerToSocketMap;
    SocketAddrToIntMap mSocketToPlayerMap;
    IntToStrMap mPlayerNameMap;

    std::vector<IntToTurnDataMap> mTurnData;

    UDPSocketPtr mSocket;
    SocketAddress mMasterPeerAddr;

    WeightedTimedMovingAverage mBytesReceivedPerSecond;
    WeightedTimedMovingAverage mBytesSentPerSecond;
    NetworkManagerState mState;

    int mBytesSentThisFrame;

    std::string mName;
    float mDropPacketChance;
    float mSimulatedLatency;
    float mTimeOfLastHello;
    float mTimeToStart;

    int mPlayerCount;

    uint32_t mHightestPlayerId;
    uint32_t mNewNetworkId;
    uint32_t mPlayerId;

    int mTurnNumber;
    int mSubTurnNumber;
    bool mIsMasterPeer;












};


#endif //MYROBOCAT_NETWORKMANAGER_H
