#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Core/AssetManager.h"
#include "../Core/TextureManager.h"
#include "./TransformComponent.h"

#include <string>

#include "../Utils/Macros.h"

class SpriteComponent: public Component {
    private:
        TransformComponent* m_transformComponent;
        SDL_Texture* m_texture;
        SDL_Rect m_src;
        SDL_Rect m_dst;
        int m_width;
        int m_height;
        bool m_isFixed;

    public:
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        SpriteComponent(std::string textureId, int width, int height, bool isFixed=false, bool flipX=false, bool flipY=false) {
            m_texture = Engine::assetManager->GetTexture(textureId);
            m_width = width;
            m_height = height;
            m_isFixed = isFixed;
            if(flipX)
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
            if(flipY)
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
        }

        static SpriteComponent* Generate(sol::table paramsTable) {
            SpriteComponent* component = new SpriteComponent(paramsTable["textureAssetId"], paramsTable["width"],
                                                             paramsTable["height"], paramsTable["isFixed"],
                                                             paramsTable["flipX"], paramsTable["flipY"]);
            return component;
        }

        void Initialize() override {
            ASSERT(!(entity->HasComponent<TransformComponent>()), "Sprite component needs a Transform Component on the entity.");
            m_transformComponent = entity->GetComponent<TransformComponent>();
            
            m_src.x = 0;
            m_src.y = 0;
            m_src.w = m_width;
            m_src.h = m_height;
        }

        void Update(float deltaTime) override {
            m_dst.x = static_cast<int>(m_transformComponent->position.x) - (m_isFixed ? 0: Engine::cameraManager->GetPosX());
            m_dst.y = static_cast<int>(m_transformComponent->position.y) - (m_isFixed ? 0: Engine::cameraManager->GetPosY());
            m_dst.w = m_width * m_transformComponent->scale;
            m_dst.h = m_height * m_transformComponent->scale;
        }

        void Render() override {
            TextureManager::Draw(m_texture, m_src, m_dst, flip);
        }

        void ModifySrcPos(int x, int y) {
            m_src.x = x;
            m_src.y = y;
        }

        void ModifySize(int w, int h) {
            m_width = w;
            m_height = h;
        }

        int GetWidth() {
            return m_width;
        }

        int GetHeight() {
            return m_height;
        }
};

#endif
