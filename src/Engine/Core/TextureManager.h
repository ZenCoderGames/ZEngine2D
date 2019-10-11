#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "./Engine.h"

class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* filePath);
        static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip);
};

#endif