#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include "./TextureManager.h"
#include "./EntityManager.h"

class AssetManager {
    private:
        EntityManager* m_entityMgr;
        std::map<std::string, SDL_Texture*> m_textureMap;
    public:
        AssetManager(EntityManager* entityManager);
        ~AssetManager();
        void AddTexture(std::string textureId, const char* filePath);
        SDL_Texture* GetTexture(std::string textureId);
        void ClearData();
};

#endif