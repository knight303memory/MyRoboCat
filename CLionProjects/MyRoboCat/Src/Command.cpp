//
// Created by Killua on 2018/2/10.
//

#include "MyRoboCatPCH.h"

std::shared_ptr<Command> Command::StaticReadAndCreate(InputMemoryBitStream &inInputStream) {
    CommandPtr retVal;

    int type = CM_INVALID;
    inInputStream.Read(type);
    uint32_t netWorkId = 0;
    inInputStream.Read(netWorkId);
    uint32_t playerId = 0;
    inInputStream.Read(playerId);

    switch (type) {
        case CM_ATTACK:
            retVal = std::make_shared<AttackCommand>();
            retVal->mNetworkId = netWorkId;
            retVal->mPlayerId = playerId;
            retVal->Read(inInputStream);
            break;
        case CM_MOVE:
            retVal = std::make_shared<MoveCommand>();
            retVal->mNetworkId = netWorkId;
            retVal->mPlayerId = playerId;
            retVal->Read(inInputStream);

        default:
            printf("Read in an unknown command type??");
            break;

    }
    return retVal;
}

void Command::Write(OutputMemoryBitStream &inOutputStream) {
    inOutputStream.Write(mCommandType);
    inOutputStream.Write(mNetworkId);
    inOutputStream.Write(mPlayerId);
}


std::shared_ptr<AttackCommand> AttackCommand::StaticCreate(uint32_t inMyNetId, uint32_t inTargetNetId) {
    AttackCommandPtr retVal;
    GameObjectPtr me = NetworkManager::sInstance->GetGameObject(inMyNetId);
    GameObjectPtr target = NetworkManager::sInstance->GetGameObject(inTargetNetId);

    uint32_t playerId = NetworkManager::sInstance->GetMyPlayerId();
    if (me && me->GetClassId() == MyRoboCat)

}