//
// Created by Killua on 2018/2/9.
//

#ifndef MYROBOCAT_INPUTMANAGER_H
#define MYROBOCAT_INPUTMANAGER_H


#include <memory>
#include "InputAction.h"

class InputManager {
public:
    static void StaticInit();

    static std::unique_ptr<InputManager> sInstance;

    void HandleInput(EInputAction inInputAction, int inKeyCode);

    void HandleMouseClick(int32_t inX, int32_t inY, uint8_t button);


};


#endif //MYROBOCAT_INPUTMANAGER_H
