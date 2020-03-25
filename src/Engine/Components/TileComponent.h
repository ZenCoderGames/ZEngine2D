#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "../Core/AssetManager.h"
#include "../Core/TextureManager.h"

class TileComponent: public Component {
    private:
        std::string m_textureId;
        SDL_Texture* m_texture;
        SDL_Rect m_src;
        SDL_Rect m_dst;
        glm::vec2 m_position;
        SDL_RendererFlip m_flip = SDL_FLIP_NONE;
        int m_tileSize, m_scale;

    public:

        TileComponent(std::string textureId, int sourceX, int sourceY, int tileSize, int x, int y, int scale) {
            m_textureId = textureId;
            m_texture = Engine::assetManager->GetTexture(textureId);
            m_scale = scale;

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

        TileComponent * clone() override {
            TileComponent* newComponent = new TileComponent(m_textureId, m_src.x, m_src.y, m_tileSize, m_dst.x, m_dst.y, m_scale);
            return newComponent;
        }

        static TileComponent* Generate(sol::table paramsTable) {
            TileComponent* component = new TileComponent(paramsTable["textureId"], paramsTable["sourceX"], paramsTable["sourceY"], paramsTable["tileSize"], paramsTable["posX"], paramsTable["posX"], paramsTable["posX"]);
            return component;
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
