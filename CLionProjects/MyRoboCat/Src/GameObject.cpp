//
// Created by Killua on 2018/2/5.
//

#include "MyRoboCatPCH.h"

GameObject::GameObject() : mIndexInWorld(-1), mCollisionRadius(0.5f), mDoesWantToDie(false), mRotation(0.f),
                           mNetworkId(0), mPlayerId(0), mColor(Colors::White), mScale(1.0f) {}

GameObject::~GameObject() {}

bool GameObject::Update(float inDeltaTime) {}

void GameObject::HandleDying() {
    //TODO
}

Vector3 GameObject::GetForwardVector() const {
    return Vector3(sinf(mRotation), -cosf(mRotation), 0.f);
}

bool GameObject::TrySelect(const Vector3 &inLocation) {
    Vector3 diff = mLocation - inLocation;
    float dist = diff.Length2D();
    if (dist <= mCollisionRadius) {
        return true;
    }

    return false;
}
