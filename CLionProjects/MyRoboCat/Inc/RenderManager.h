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

    void AddComponent();

    void RemoveComponent();

    int GetComponentIndex() const;

private:
    RenderManager();

    vector<>

};


#endif //MYROBOCAT_RENDERMANAGER_H
