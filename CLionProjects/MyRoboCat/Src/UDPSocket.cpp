//
// Created by Killua on 2018/2/5.
//

#include "MyRoboCatPCH.h"

int UDPSocket::Bind(const SocketAddress &inToAddress) {
    int err = bind(mSocket, &inToAddress.mSockAddr, inToAddress.GetSize());
    if (err < 0) {
        SocketUtil::ReportError("UDPSocket::Bind");
        return SocketUtil::GetLastError();
    }
    return NO_ERROR;
}


int UDPSocket::SendTo(const void *inToSend, size_t inLength, const SocketAddress &inToAdress) {
    int byteSentCount = sendto(mSocket, static_cast<const char *>(inToSend), inLength, 0, &inToAdress.mSockAddr,
                               inToAdress.GetSize());
    if (byteSentCount <= 0) {
        SocketUtil::ReportError("UDPSocket::SendTo");
        return -SocketUtil::GetLastError();
    } else {
        return byteSentCount;
    }
}

int UDPSocket::ReceiveFrom(void *inToReceive, int inMaxLength, SocketAddress &outFromAddress) {
    socklen_t fromLength = outFromAddress.GetSize();

    int readByteCount = recvfrom(mSocket, static_cast<char *>(inToReceive), inMaxLength, 0, &outFromAddress.mSockAddr,
                                 &fromLength);

    if (readByteCount < 0) {
        int err = SocketUtil::GetLastError();
        if (err == WSAEWOULDBLOCK) {
            return 0;
        } else if (err == WSAECONNRESET) {
            return -WSAECONNRESET;
        } else {
            SocketUtil::ReportError("UDPSocket :: ReceiveFrom");
            return -err;
        }
    } else {
        return readByteCount;
    }

}

UDPSocket::~UDPSocket() {
    close(mSocket);
}

int UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking) {
    int flags = fcntl(mSocket, F_GETFL, 0);
    flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    int result = fcntl(mSocket, F_SETFL, flags);

    if (result == SOCKET_ERROR) {
        SocketUtil::ReportError("UDPSocket::SetNonBlockingMode");
        return SocketUtil::GetLastError();
    } else {
        return NO_ERROR;
    }
}