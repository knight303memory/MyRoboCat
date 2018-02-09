//
// Created by Killua on 2018/2/9.
//

#ifndef MYROBOCAT_SP_H
#define MYROBOCAT_SP_H

#include <SDL_rect.h>
#include "GameObject.h"
#include "Texture.h"

class SpriteComponent {

public:
    SpriteComponent(GameObject *inGameObject);

    ~SpriteComponent();

    virtual void Draw(const SDL_Rect &inViewTransform);

    void SetTexture(TexturePtr inTexture) {
        mTexture = inTexture;
    }

    Vector3 GetOrigin() const {
        return mOrigin;
    }

    void SetOrigin(const Vector3 &inOrigin) {
        mOrigin = inOrigin;
    }


private:
    Vector3 mOrigin;
    TexturePtr mTexture;
    GameObject *mGameObject;
};


typedef std::shared_ptr<SpriteComponent> SpriteComponentPtr;

#endif //MYROBOCAT_SP_H
