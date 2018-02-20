//
// Created by Killua on 2018/2/20.
//

#ifndef MYROBOCAT_ROBOCAT_H
#define MYROBOCAT_ROBOCAT_H


#include "GameObject.h"
#include "NetworkManager.h"
#include "SpriteComponent.h"

class MyRoboCat : public GameObject {
public:
    CLASS_INDENTIFICATION('RCAT', GameObject);
    enum RoboCatState {
        RC_IDLE,
        RC_MOVING,
        RC_ATTACK,
    };

    static GameObjectPtr StaticCreate() {
        return NetworkManager::sInstance->RegisterAndReturn(new MyRoboCat());
    }

    MyRoboCat *GetAsCat() override {
        return this;
    }

    bool Update(float inDeltaTime) override;

    void UpdateIdleState(float inDeltaTime);

    void UpdateMovingState(float inDeltaTime);

    void UpdateAttactState(float inDeltaTime);

    bool MoveToLocation(float inDeltaTime, const Vector3 &inLocation);

    void UpdateRotation(const Vector3 &inTarget);

    void EnterMovingState(const Vector3 &inTarget);

    void EnterAttackState(uint32_t inTargetNetId);

    void TakeDemage(int inDmgAmount);

    virtual void HandleDying() override;

    MyRoboCat();

    void WriteForCRC(OutputMemoryBitStream &inStream) override;

private:
    Vector3 mMoveLocation;
    SpriteComponentPtr mSpriteComponent;
    int mHealth;
    RoboCatState mState;
    uint32_t mTargetNetId;
    GameObjectPtr mTargetCat;
    float mTimeSinceLastAttack;
};

typedef std::shared_ptr<MyRoboCat> RoboCatPtr;
#endif //MYROBOCAT_ROBOCAT_H
