//
// Created by Killua on 2018/2/9.
//

#ifndef MYROBOCAT_RENDERMANAGER_H
#define MYROBOCAT_RENDERMANAGER_H


#include <memory>

class RenderManager {
public:

    static void StaticInit();

    static std::unique_ptr<RenderManager> sInstance;

    void Render();

    void RenderComponents();

    void AddComponent(SpriteComponent *inComponent);

    void RemoveComponent(SpriteComponent *inComponent);

    int GetComponentIndex(SpriteComponent *inComponent) const;

private:
    RenderManager();

    std::vector<SpriteComponent *> mComponents;

    SDL_Rect mViewTransform;
};


#endif //MYROBOCAT_RENDERMANAGER_H
