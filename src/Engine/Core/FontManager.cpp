#include "./FontManager.h"

TTF_Font* FontManager::LoadFont(const char* filePath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(filePath, fontSize);
    ASSERT(font==nullptr, STR_CONCAT("Unable to load font: ", filePath));
    return font;
}
        
void FontManager::Draw(SDL_Texture* texture, SDL_Rect dstRect) {
    SDL_RenderCopy(Engine::renderer, texture, NULL, &dstRect);
}