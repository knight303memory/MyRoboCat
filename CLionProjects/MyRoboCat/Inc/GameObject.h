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


public:
    const Vector3 &getLocation() const {
        return mLocation;
    }

    void setLocation(const Vector3 &mLocation) {
        GameObject::mLocation = mLocation;
    }

    const Vector3 &getColor() const {
        return mColor;
    }

    void setColor(const Vector3 &mColor) {
        GameObject::mColor = mColor;
    }

    float getCollisionRadius() const {
        return mCollisionRadius;
    }

    void setCollisionRadius(float mCollisionRadius) {
        GameObject::mCollisionRadius = mCollisionRadius;
    }

    float getRotation() const {
        return mRotation;
    }

    void setRotation(float mRotation) {
        GameObject::mRotation = mRotation;
    }

    float getScale() const {
        return mScale;
    }

    void setScale(float mScale) {
        GameObject::mScale = mScale;
    }

    int getIndexInWorld() const {
        return mIndexInWorld;
    }

    void setIndexInWorld(int mIndexInWorld) {
        GameObject::mIndexInWorld = mIndexInWorld;
    }

    uint32_t getNetworkId() const {
        return mNetworkId;
    }

    void setNetworkId(uint32_t mNetworkId) {
        GameObject::mNetworkId = mNetworkId;
    }

    uint32_t getPlayerId() const {
        return mPlayerId;
    }

    void setPlayerId(uint32_t mPlayerId) {
        GameObject::mPlayerId = mPlayerId;
    }

    bool isDoesWantToDie() const {
        return mDoesWantToDie;
    }

    void setDoesWantToDie(bool mDoesWantToDie) {
        GameObject::mDoesWantToDie = mDoesWantToDie;
    }

    bool isSelected() const {
        return mSelected;
    }

    void setSelected(bool mSelected) {
        GameObject::mSelected = mSelected;
    }

    Vector3 GetForwardVector() const;

    virtual void WriteForCRC(OutputMemoryBitStream &inStream) { (void) inStream; }

    virtual bool TrySelect(const Vector3 &inLocation);

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
