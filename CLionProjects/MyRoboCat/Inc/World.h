//
// Created by Killua on 2018/2/6.
//

#ifndef MYROBOCAT_WORLD_H
#define MYROBOCAT_WORLD_H

#include <memory>
#include <vector>
#include "GameObject.h"

const float kWorldZoomFactor = 100.0f;
const float kWorldWidth = 12.8f;
const float kWorldHeight = 7.2f;


class World {
public:
    static void StaticInit();

    static std::unique_ptr<World> sInstance;

    void AddGameObject(GameObjectPtr inGameObject);

    void RemoveGameObject(GameObjectPtr inGameObject);

    void Update(float inDeltaTime);

    const std::vector<GameObjectPtr> &GetGameObjects() const { return mGameObjects; }

    uint32_t TrySelectGameObject(const Vector3 &inSelectLoc);

private:
    World();

    std::vector<GameObjectPtr> mGameObjects;

};


#endif //MYROBOCAT_WORLD_H
