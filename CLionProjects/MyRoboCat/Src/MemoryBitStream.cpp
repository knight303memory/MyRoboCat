//
// Created by Killua on 2018/2/10.
//

#include "MyRoboCatPCH.h"


void OutputMemoryBitStream::WriteBits(uint8_t inData, uint32_t inBitCount) {
    uint32_t nextBitHead = mBitHead + static_cast<uint32_t >(inBitCount);

    if (nextBitHead > mBitCapacity) {
        ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));

    }

    uint32_t byteOffset = mBitHead >> 3;
    uint32_t bitOffset = mBitHead & 0x7;

    uint8_t currentMask = ~(0xff << bitOffset);
    mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

    uint32_t bitsFreeThisByte = 8 - bitOffset;

    if (bitsFreeThisByte < inBitCount) {
        mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
    }

    mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void *inData, uint32_t inBitCount) {
    const char *srcByte = static_cast<const char *>(inData);
    while (inBitCount > 8) {
        WriteBits(*srcByte, 8);
        ++srcByte;
        inBitCount -= 8;
    }

    if (inBitCount > 0) {
        WriteBits(*srcByte, inBitCount);
    }
}


void OutputMemoryBitStream::Write(const Vector3 &inVector) {

    Write(inVector.mX);
    Write(inVector.mY);
    Write(inVector.mZ);

}


void InputMemoryBitStream::Read(Vector3 &inVector) {
    Read(inVector.mX);
    Read(inVector.mY);
    Read(inVector.mZ);
}

void OutputMemoryBitStream::Write(const Quaternion &inQuat) {
    float precision = (2.f / 65535.f);
    Write(ConvertFromFixed(inQuat.mX, -1.f, precision), 16);
    Write(ConvertFromFixed(inQuat.mY, -1.f, precision), 16);
    Write(ConvertFromFixed(inQuat.mZ, -1.f, precision), 16);
    Write(inQuat.mW < 0);
}

void OutputMemoryBitStream::ReallocBuffer(uint32_t inNewBitCapacity) {
    if (mBuffer == nullptr) {
        mBuffer = static_cast<char *>(std::malloc(inNewBitCapacity >> 3));
        memset(mBuffer, 0, inNewBitCapacity >> 3);
    } else {
        char *tempBuffer = static_cast<char *>(std::malloc(inNewBitCapacity >> 3));
        memset(tempBuffer, 0, inNewBitCapacity >> 3);
        memcpy(tempBuffer, mBuffer, mBitCapacity >> 3);
        std::free(mBuffer);
        mBuffer = tempBuffer;
    }

    mBitCapacity = inNewBitCapacity;
}


void InputMemoryBitStream::ReadBits(uint8_t &outData, uint32_t inBitCount) {
    uint32_t byteOffset = mBitHead >> 3;
    uint32_t bitOffset = mBitHead & 0x7;

    outData = static_cast< uint8_t >( mBuffer[byteOffset] ) >> bitOffset;

    uint32_t bitsFreeThisByte = 8 - bitOffset;
    if (bitsFreeThisByte < inBitCount) {
        //we need another byte
        outData |= static_cast< uint8_t >( mBuffer[byteOffset + 1] ) << bitsFreeThisByte;
    }

    //don't forget a mask so that we only read the bit we wanted...
    outData &= (~(0x00ff << inBitCount));

    mBitHead += inBitCount;
}

void InputMemoryBitStream::ReadBits(void *outData, uint32_t inBitCount) {
    uint8_t *destByte = reinterpret_cast< uint8_t * >( outData );
    //write all the bytes
    while (inBitCount > 8) {
        ReadBits(*destByte, 8);
        ++destByte;
        inBitCount -= 8;
    }
    //write anything left
    if (inBitCount > 0) {
        ReadBits(*destByte, inBitCount);
    }
}

void InputMemoryBitStream::Read(Quaternion &outQuat) {
    float precision = (2.f / 65535.f);

    uint32_t f = 0;

    Read(f, 16);
    outQuat.mX = ConvertFromFixed(f, -1.f, precision);
    Read(f, 16);
    outQuat.mY = ConvertFromFixed(f, -1.f, precision);
    Read(f, 16);
    outQuat.mZ = ConvertFromFixed(f, -1.f, precision);

    outQuat.mW = sqrtf(1.f -
                       outQuat.mX * outQuat.mX +
                       outQuat.mY * outQuat.mY +
                       outQuat.mZ * outQuat.mZ);
    bool isNegative;
    Read(isNegative);

    if (isNegative) {
        outQuat.mW *= -1;
    }
}