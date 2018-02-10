//
// Created by Killua on 2018/2/10.
//

#ifndef MYROBOCAT_NETWORKMANAGER_H
#define MYROBOCAT_NETWORKMANAGER_H


#include <cstdint>
#include <memory>
#include "SocketAddress.h"
#include "GameObject.h"

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


private:
    
};


#endif //MYROBOCAT_NETWORKMANAGER_H
