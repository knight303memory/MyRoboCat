//
// Created by Killua on 2018/2/9.
//

#include "MyRoboCatPCH.h"


std::unique_ptr<GraphicsDriver> GraphicsDriver::sInstance = nullptr;

bool GraphicsDriver::StaticInit(SDL_Window *inWnd) {
    GraphicsDriver *newGraphicsDriver = new GraphicsDriver();
    bool result = newGraphicsDriver->Init(inWnd);

    if (!result) {
        delete newGraphicsDriver;
    } else {
        sInstance.reset(newGraphicsDriver);
    }

    return result;
}


bool GraphicsDriver::Init(SDL_Window *inWnd) {
    mRenderer = SDL_CreateRenderer(inWnd, -1, SDL_RENDERER_ACCELERATED);

    if (mRenderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "failed to create renderer");
        return false;

    }

    SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
    SDL_RenderSetLogicalSize(mRenderer, 1280, 720);

    return true;
}

GraphicsDriver::GraphicsDriver() : mRenderer(nullptr) {}

GraphicsDriver::~GraphicsDriver() {
    if (mRenderer != nullptr) {
        SDL_DestroyRenderer(mRenderer);
    }
}


void GraphicsDriver::Clear() {
    SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer);
}

void GraphicsDriver::Present() {
    SDL_RenderPresent(mRenderer);
}


SDL_Rect &GraphicsDriver::GetLogicalViewport() {
    SDL_RenderGetLogicalSize(mRenderer, &mViewport.w, &mViewport.h);
    return mViewport;
}


SDL_Renderer *GraphicsDriver::GetRenderer() {
    return mRenderer;
}