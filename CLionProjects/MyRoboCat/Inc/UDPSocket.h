//
// Created by Killua on 2018/2/5.
//

#ifndef MYROBOCAT_UDPSOCKET_H
#define MYROBOCAT_UDPSOCKET_H


#include <memory>
#include "SocketAddress.h"

typedef int SOCKET;

class UDPSocket {

public:
    ~UDPSocket();

    int Bind(const SocketAddress &inToAddress);

    int SendTo(const void *inToSend, size_t inLength, const SocketAddress &inToAdress);

    int ReceiveFrom(void *inToReceive, int inMaxLength, SocketAddress &outFromAddress);

    int SetNonBlockingMode(bool inShouldBeNonBlocking);


private:
    friend class SocketUtil;

    UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}

    SOCKET mSocket;

};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

#endif //MYROBOCAT_UDPSOCKET_H
