//
// Created by Killua on 2018/2/9.
//

#include "MyRoboCatPCH.h"

std::unique_ptr<RenderManager> RenderManager::sInstance = nullptr;

RenderManager::RenderManager() {
    SDL_Rect viewPort = GraphicsDriver::sInstance->GetLogicalViewport();

    mViewTransform.x = viewPort.w / 2;
    mViewTransform.y = viewPort.h / 2;
    mViewTransform.w = static_cast<int>(kWorldZoomFactor);
    mViewTransform.h = static_cast<int>(kWorldZoomFactor);
}

void RenderManager::StaticInit() {
    sInstance.reset(new RenderManager());
}

void RenderManager::AddComponent(SpriteComponent *inComponent) {
    mComponents.push_back(inComponent);
}

void RenderManager::RemoveComponent(SpriteComponent *inComponent) {
    int index = GetComponentIndex(inComponent);

    if (index != -1) {
        int lastIndex = static_cast<int>(mComponents.size() - 1);
        if (index != lastIndex) {
            mComponents[index] = mComponents[lastIndex];
        }
        mComponents.pop_back();
    }
}

int RenderManager::GetComponentIndex(SpriteComponent *inComponent) const {
    for (int i = 0, c = static_cast<int>(mComponents.size()); i < c; ++i) {
        if (mComponents[i] == inComponent) {
            return i;
        }
    }

    return -1;
}

void RenderManager::RenderComponents() {
    for (auto cIt = mComponents.begin(), end = mComponents.end(); cIt != end; ++cIt) {
        (*cIt)->Draw(mViewTransform);
    }
}

void RenderManager::Render() {
    GraphicsDriver::sInstance->Clear();
    RenderManager::sInstance->RenderComponents();
    HUD::sInstance->Render();
    GraphicsDriver::sInstance->Present();
}


