#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include "./TextureManager.h"
#include "./FontManager.h"
#include <SDL2/SDL_ttf.h>
#include "./EntityManager.h"

class AssetManager {
    private:
        EntityManager* m_entityMgr;
        std::map<std::string, SDL_Texture*> m_textureMap;
        std::map<std::string, TTF_Font*> m_fontMap;
    public:
        AssetManager(EntityManager* entityManager);
        ~AssetManager();

        void AddTexture(std::string textureId, const char* filePath);
        SDL_Texture* GetTexture(std::string textureId);

        void AddFont(std::string fontId, const char* filePath, int fontSize);
        TTF_Font* GetFont(std::string fontId);

        void ClearData();
};

#endif