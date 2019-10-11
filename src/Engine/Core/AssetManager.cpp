#include "./AssetManager.h"

AssetManager::AssetManager(EntityManager* entityManager):m_entityMgr(entityManager) {

}

AssetManager::~AssetManager() {

}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    m_textureMap[textureId] = TextureManager::LoadTexture(filePath);
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return m_textureMap[textureId];
}

void AssetManager::ClearData() {
    m_textureMap.clear();
}