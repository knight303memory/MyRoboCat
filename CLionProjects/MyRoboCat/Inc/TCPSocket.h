//
// Created by Killua on 2018/2/4.
//

#ifndef MYROBOCAT_TCPSOCKET_H
#define MYROBOCAT_TCPSOCKET_H


#include "SocketAddress.h"

typedef int SOCKET;

class TCPSocket {
public:
    ~TCPSocket();

    int Connect(const SocketAddress &inAddress);

    int Bind(const SocketAddress &inToAddress);

    int Listen(int inBackLog = 32);

    std::shared_ptr<TCPSocket> Accept(SocketAddress &inFromAddress);

    int32_t Send(const void *inData, size_t inLen);

    int32_t Receive(void *inBuffer, size_t inLen);

private:
    friend class SocketUtil;

    TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}

    SOCKET mSocket;
};

typedef std::shared_ptr<TCPSocket> TCPSocketPtr;


#endif //MYROBOCAT_TCPSOCKET_H
