//
// Created by Killua on 2018/2/5.
//

#ifndef MYROBOCAT_GAMEOBJECT_H
#define MYROBOCAT_GAMEOBJECT_H

#include <cstdint>
#include <memory>
#include "RoboMath.h"

class MyRoboCat;

#define CLASS_INDENTIFICATION(inCode, inClass)\
enum{kClassId = inCode};\
virtual uint32_t GetClassId()const{return kClassId;}\
static GameObject* CreateInstance(){return static_cast<GameObject *>(new inClass());}\


class GameObject {
public:
    CLASS_INDENTIFICATION('GOBJ', GameObject);

    GameObject();

    virtual ~GameObject();

    virtual MyRoboCat *GetAsCat() { return nullptr; }

    virtual bool HandleCollisionWithCat(MyRoboCat *inCat) {
        (void) inCat;
        return true;
    }

    virtual bool Update(float inDeltaTime);

    virtual void HandleDying();


protected:
    Vector3 mLocation;
    Vector3 mColor;
    float mCollisionRadius;
    float mRotation;
    float mScale;
    int mIndexInWorld;

    uint32_t mNetworkId;
    uint32_t mPlayerId;

    bool mDoesWantToDie;
    bool mSelected;
};

typedef std::shared_ptr<GameObject> GameObjectPtr;


#endif //MYROBOCAT_GAMEOBJECT_H
