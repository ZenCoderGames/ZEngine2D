#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "../Core/AssetManager.h"
#include "../Core/TextureManager.h"

class TileComponent: public Component {
    private:
        SDL_Texture* m_texture;
        SDL_Rect m_src;
        SDL_Rect m_dst;
        glm::vec2 m_position;
        SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    public:

        TileComponent(std::string textureId, int sourceX, int sourceY, int tileSize, int x, int y, int scale) {
            m_texture = Engine::assetManager->GetTexture(textureId);
            
            m_src.x = sourceX;
            m_src.y = sourceY;
            m_src.w = tileSize;
            m_src.h = tileSize;

            m_dst.x = x;
            m_dst.y = y;
            m_dst.w = tileSize * scale;
            m_dst.h = tileSize * scale;

            m_position.x = x;
            m_position.y = y;
        }

        void Update(float deltaTime) override {
            m_dst.x = m_position.x - Engine::cameraManager->GetPosX();
            m_dst.y = m_position.y - Engine::cameraManager->GetPosY();
        }

        void Render() override {
            TextureManager::Draw(m_texture, m_src, m_dst, m_flip);
        }
};

#endif
