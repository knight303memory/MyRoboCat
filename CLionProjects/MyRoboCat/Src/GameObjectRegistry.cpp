//
// Created by Killua on 2018/2/5.
//

#include "MyRoboCatPCH.h"

std::unique_ptr<GameObjectRegistry> GameObjectRegistry::sInstance = nullptr;

void GameObjectRegistry::StaticInit() {
    sInstance.reset(new GameObjectRegistry());
}

GameObjectRegistry::GameObjectRegistry() {}

void GameObjectRegistry::RegisterCreationFunction(uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction) {
    mNameToGameObjectCreationFuntionMap[inFourCCName] = inCreationFunction;
}

GameObjectPtr GameObjectRegistry::CreateGameObject(uint32_t inFourCCName) {
    GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFuntionMap[inFourCCName];

    GameObjectPtr gameObject = creationFunc();

    World::sInstance->AddGameObject(gameObject);

    return gameObject;
}