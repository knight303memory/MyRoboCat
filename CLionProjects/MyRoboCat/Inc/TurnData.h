//
// Created by Killua on 2018/2/16.
//

#ifndef MYROBOCAT_TURNDATA_H
#define MYROBOCAT_TURNDATA_H


#include <cstdint>
#include "CommandList.h"

class TurnData {
public:
    TurnData() : mPlayerId(0), mRandomValue(0), mCRC(0) {}


    TurnData(int playerId, uint32_t inRandomValue, uint32_t inCRC, CommandList &inCommandList) :
            mPlayerId(playerId), mRandomValue(mRandomValue), mCRC(inCRC), mCommandList(inCommandList) {}

    void Write(OutputMemoryBitStream &inOutputStream);

    void Read(InputMemoryBitStream &inInputStream);

    int GetPlayerId() const {
        return mPlayerId;
    }

    uint32_t GetRandomValue() const {
        return mRandomValue;

    }

    uint32_t GetCRC() const {
        return mCRC;
    }

    CommandList &GetCommandList() {
        return mCommandList;
    }

private:
    int mPlayerId;
    uint32_t mRandomValue;
    uint32_t mCRC;
    CommandList mCommandList;
};


#endif //MYROBOCAT_TURNDATA_H
