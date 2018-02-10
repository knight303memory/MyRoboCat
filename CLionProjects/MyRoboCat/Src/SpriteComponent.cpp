//
// Created by Killua on 2018/2/9.
//


#include "MyRoboCatPCH.h"

SpriteComponent::SpriteComponent(GameObject *inGameObject) : mGameObject(inGameObject) {
    float textureWidth = 128.f, textureHeight = 128.f;
    mOrigin = Vector3(textureWidth * 0.5f, textureHeight * 0.5f, 0.f);

    RenderManager::sInstance->AddComponent(this);

}
