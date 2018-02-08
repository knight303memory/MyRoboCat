//
// Created by Killua on 2018/2/8.
//

#ifndef MYROBOCAT_WINDOWMANAGER_H
#define MYROBOCAT_WINDOWMANAGER_H


#include <memory>
#include <SDL_video.h>

class WindowManager {
public:
    static bool StaticInit();

    static std::unique_ptr<WindowManager> sInstance;

    SDL_Window *GetMainWindow() const {
        return mMainWindow;
    }

    ~WindowManager();


private:
    WindowManager(SDL_Window *inMainWindow);

    SDL_Window *mMainWindow;

};


#endif //MYROBOCAT_WINDOWMANAGER_H
