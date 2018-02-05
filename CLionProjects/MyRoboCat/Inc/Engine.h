//
// Created by Killua on 2018/2/3.
//

#ifndef MYROBOCAT_ENGINE_H
#define MYROBOCAT_ENGINE_H

#include <SDL_events.h>

class Engine {
public:
    static bool StaticInit();

    virtual ~Engine();

    static std::unique_ptr<Engine> sInstance;

    virtual int Run();

    void SetShouldKeepingRunning(bool inShouldKeepRunning) {
        mShouldKeepRunning = inShouldKeepRunning;
    }


protected:
    Engine();

    virtual void DoFrame();


private:
    int DoRunLoop();

    bool mShouldKeepRunning;


};


#endif //MYROBOCAT_ENGINE_H
