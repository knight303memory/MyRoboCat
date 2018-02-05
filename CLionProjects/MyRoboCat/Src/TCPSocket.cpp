//
// Created by Killua on 2018/2/4.
//

#include "MyRoboCatPCH.h"


int TCPSocket::Connect(const SocketAddress &inAddress) {
    int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
    if (err < 0) {

    }
}

int TCPSocket::Listen(int inBackLog) {
    int err = listen(mSocket, inBackLog);
    if (err < 0) {
        SocketUtil::ReportError("TCPSocket::listen");

    }
}


std::shared_ptr<TCPSocket> TCPSocket::Accept(SocketAddress &inFromAddress) {
    socklen_t length = inFromAddress.GetSize();
    SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);

    if (newSocket != INVALID_SOCKET) {
        return TCPSocketPtr(new TCPSocket(newSocket));
    } else {
        SocketUtil::ReportError("TCPSocket::Accpet");
        return nullptr;
    }
}

int32_t TCPSocket::Send(const void *inData, size_t inLen) {
    int bytesSentCount = send(mSocket, static_cast<const char *>(inData), inLen, 0);
    if (bytesSentCount < 0) {
        SocketUtil::ReportError("TCPSocket::Send");
        return -SocketUtil::GetLastError();
    }
    return bytesSentCount;
}


int32_t TCPSocket::Receive(void *inBuffer, size_t inLen) {
    int byteReceivedCount = recv(mSocket, static_cast<char *>(inBuffer), inLen, 0);
    if (byteReceivedCount < 0) {
        SocketUtil::ReportError("TCPSocket::Receive");
        return -SocketUtil::GetLastError();
    }
    return byteReceivedCount;
}

int TCPSocket::Bind(const SocketAddress &inToAddress) {
    int err = bind(mSocket, &inToAddress.mSockAddr, inToAddress.GetSize());
    if (err != 0) {
        SocketUtil::ReportError("TCPSocket :: Bind");
        return SocketUtil::GetLastError();
    }

    return NO_ERROR;
}

TCPSocket::~TCPSocket() {
    close(mSocket);
}