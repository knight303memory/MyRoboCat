//
// Created by Killua on 2018/2/9.
//

#ifndef MYROBOCAT_TEXTURE_H
#define MYROBOCAT_TEXTURE_H


#include <cstdint>
#include <SDL_system.h>
#include <memory>

class Texture {
public:
    Texture(uint32_t inWidth, uint32_t inHeight, SDL_Texture *inTexture);

    ~Texture();

    uint32_t GetWidth() const {
        return mWidth;
    }

    uint32_t GetHeight() const {
        return mHeight;
    }

    SDL_Texture *GetData() const {
        return mTexture;
    }


private:
    uint32_t mWidth;
    uint32_t mHeight;
    SDL_Texture *mTexture;
};

typedef std::shared_ptr<Texture> TexturePtr;

#endif //MYROBOCAT_TEXTURE_H
