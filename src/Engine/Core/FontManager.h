#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "./Engine.h"
#include "../Utils/Macros.h"

class FontManager {
    public:
        static TTF_Font* LoadFont(const char* filePath, int fontSize);
        static void Draw(SDL_Texture* texture, SDL_Rect dstRect);
};

#endif