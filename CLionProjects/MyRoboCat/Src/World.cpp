//
// Created by Killua on 2018/2/6.
//

#include "MyRoboCatPCH.h"

std::unique_ptr<World> sInstance = nullptr;

void World::StaticInit() {
    sInstance.reset(new World());
}

World::World() {}

void World::AddGameObject(GameObjectPtr inGameObject) {
    mGameObjects.push_back(inGameObject);
    inGameObject->setIndexInWorld(static_cast<int>(mGameObjects.size() - 1));
}

void World::RemoveGameObject(GameObjectPtr inGameObject) {
    int index = inGameObject->getIndexInWorld();

    int lastIndex = static_cast<int>(mGameObjects.size() - 1);

    if (index != lastIndex) {
        mGameObjects[index] = mGameObjects[lastIndex];
        mGameObjects[index]->setIndexInWorld(index);
    }

    inGameObject->setIndexInWorld(-1);
    mGameObjects.pop_back();
}

void World::Update(float inDeltaTime) {
    for (int i = 0, c = static_cast<int>(mGameObjects.size()); i < c; ++i) {
        GameObjectPtr go = mGameObjects[i];

        if (!go->isDoesWantToDie()) {
            go->Update(inDeltaTime);
        }

        if (go->isDoesWantToDie()) {
            RemoveGameObject(go);
            go->HandleDying();
            --i;
            --c;
        }

    }
}


uint32_t World::TrySelectGameObject(const Vector3 &inSelectLoc) {
    for (auto &g : mGameObjects) {
        if (g->TrySelect(inSelectLoc)) {
            return g->getNetworkId();
        }
    }
    return 0;
}

