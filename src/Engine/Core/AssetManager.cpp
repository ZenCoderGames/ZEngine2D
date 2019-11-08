#include "./AssetManager.h"
#include "../Utils/Macros.h"

AssetManager::AssetManager(EntityManager* entityManager):m_entityMgr(entityManager) {

}

AssetManager::~AssetManager() {

}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    m_textureMap[textureId] = TextureManager::LoadTexture(filePath);
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    ASSERT(m_textureMap[textureId]==nullptr, STR_CONCAT("Invalid texture id: ", textureId));
    return m_textureMap[textureId];
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
    m_fontMap[fontId] = FontManager::LoadFont(filePath, fontSize);
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
    ASSERT(m_fontMap[fontId]==nullptr, STR_CONCAT("Invalid font id: ", fontId));
    return m_fontMap[fontId];
}

void AssetManager::ClearData() {
    m_textureMap.clear();
    m_fontMap.clear();
}