//
// Created by Killua on 2018/2/9.
//

#include <SDL_image.h>
#include "MyRoboCatPCH.h"

std::unique_ptr<TextureManager> TextureManager::sInstance = nullptr;

void TextureManager::StaticInit() {

    sInstance.reset(new TextureManager());
}

TextureManager::TextureManager() {
    CacheTexture("cat", "../Assets/car.png");
    CacheTexture("mouse", "../Assets/mouse.png");
    CacheTexture("yarn", "../Assets/yarn.png");
}

TexturePtr TextureManager::GetTexture(const std::string &inTextureName) {
    return mNameToTextureMap[inTextureName];
}

bool TextureManager::CacheTexture(std::string inName, const char *inFileName) {
    SDL_Texture *texture = IMG_LoadTexture(GraphicsDriver::sInstance->GetRenderer(), inFileName);

    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture:%s", inFileName);
        return false;

    }

    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    TexturePtr newTexture(new Texture(w, h, texture));

    mNameToTextureMap[inName] = newTexture;

    return true;
}

