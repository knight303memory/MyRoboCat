//
// Created by Killua on 2018/2/9.
//


#include "MyRoboCatPCH.h"

SpriteComponent::SpriteComponent(GameObject *inGameObject) : mGameObject(inGameObject) {
    float textureWidth = 128.f, textureHeight = 128.f;
    mOrigin = Vector3(textureWidth * 0.5f, textureHeight * 0.5f, 0.f);

    RenderManager::sInstance->AddComponent(this);

}

SpriteComponent::~SpriteComponent() {
    RenderManager::sInstance->RemoveComponent(this);
}

void SpriteComponent::Draw(const SDL_Rect &inViewTransform) {
    if (mTexture) {
        Vector3 color = mGameObject->getColor();
        uint8_t r = static_cast<uint8_t >(color.mX * 255);
        uint8_t g = static_cast<uint8_t >(color.mY * 255);
        uint8_t b = static_cast<uint8_t >(color.mZ * 255);

        SDL_SetTextureColorMod(mTexture->GetData(), r, g, b);

        Vector3 objLocation = mGameObject->getLocation();
        float objScale = mGameObject->getScale();
        SDL_Rect dsRect;

        dsRect.w = static_cast<int>(mTexture->GetWidth() * objScale);
        dsRect.h = static_cast<int>(mTexture->GetHeight() * objScale);
        dsRect.x = static_cast<int>(objLocation.mX * inViewTransform.w + inViewTransform.x - dsRect.w / 2);
        dsRect.y = static_cast<int>(objLocation.mY * inViewTransform.h + inViewTransform.y - dsRect.h / 2);

        SDL_Renderer *render = GraphicsDriver::sInstance->GetRenderer();

        SDL_RenderCopyEx(render, mTexture->GetData(), nullptr, &dsRect, RoboMath::ToDegrees(mGameObject->getRotation()),
                         nullptr, SDL_FLIP_NONE);

        if (mGameObject->getNetworkId() == InputManager::sInstance->) {

        }
    }
}

