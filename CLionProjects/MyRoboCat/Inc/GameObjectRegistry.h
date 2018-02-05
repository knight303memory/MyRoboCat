//
// Created by Killua on 2018/2/5.
//

#ifndef MYROBOCAT_GAMEOBJECTREGISTRY_H
#define MYROBOCAT_GAMEOBJECTREGISTRY_H

#include <memory>
#include <unordered_map>

typedef GameObjectPtr (*GameObjectCreationFunc)();

class GameObjectRegistry {

public:
    static void StaticInit();

    static std::unique_ptr<GameObjectRegistry> sInstance;

    void RegisterCreationFunction(uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction);

    GameObjectPtr CreateGameObject(uint32_t inFourCCName);

private:
    GameObjectRegistry();

    std::unordered_map<uint32_t, GameObjectCreationFunc> mNameToGameObjectCreationFuntionMap;
};


#endif //MYROBOCAT_GAMEOBJECTREGISTRY_H
