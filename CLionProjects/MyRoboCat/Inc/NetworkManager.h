//
// Created by Killua on 2018/2/10.
//

#ifndef MYROBOCAT_NETWORKMANAGER_H
#define MYROBOCAT_NETWORKMANAGER_H


#include <cstdint>
#include <memory>
#include "SocketAddress.h"

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

    void ProcessPacketsHello(InputMemoryBitStream &inInputStream, const SocketAddress &inFromAddress);
    

};


#endif //MYROBOCAT_NETWORKMANAGER_H
