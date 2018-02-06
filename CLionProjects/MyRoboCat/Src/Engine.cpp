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

}
