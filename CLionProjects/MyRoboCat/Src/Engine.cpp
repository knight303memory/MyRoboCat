//
// Created by Killua on 2018/2/3.
//


#include "MyRoboCatPCH.h"

unique_ptr<Engine> Engine::sInstance = nullptr;

Engine::Engine() : mShouldKeepRunning(true) {

}

bool Engine::StaticInit() {

    RandGen::StaticInit();

    SocketUtil::StaticInit();

    GameObjectRegistry::StaticInit();

    World::StaticInit();

    ScoreBoardManager::StaticInit();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (!WindowManager::StaticInit()) {
        return false;
    }

    if (!GraphicsDriver::StaticInit(WindowManager::sInstance->GetMainWindow())) {
        return false;
    }


}
