#include "./TextureManager.h"

#include "../Utils/Macros.h"

SDL_Texture* TextureManager::LoadTexture(const char* filePath) {
    SDL_Surface* surface = IMG_Load(filePath);
    ASSERT(surface==NULL, STR_CONCAT("Invalid Texture Path - ", filePath));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Engine::renderer, texture, &srcRect, &dstRect, 0.0, NULL, flip);
}