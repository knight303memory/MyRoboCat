//
// Created by Killua on 2018/2/9.
//

#ifndef MYROBOCAT_TEXTUREMANAGER_H
#define MYROBOCAT_TEXTUREMANAGER_H


#include <memory>
#include <string>
#include <unordered_map>
#include "Texture.h"

class TextureManager {
public:
    static void StaticInit();

    static std::unique_ptr<TextureManager> sInstance;

    TexturePtr GetTexture(const std::string &inTextureName);


private:
    TextureManager();

    bool CacheTexture(std::string inName, const char *inFileName);

    std::unordered_map<std::string, TexturePtr> mNameToTextureMap;
};


#endif //MYROBOCAT_TEXTUREMANAGER_H
