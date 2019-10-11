#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Core/AssetManager.h"
#include "../Core/TextureManager.h"
#include "./TransformComponent.h"

#include "../Utils/Macros.h"

class SpriteComponent: public Component {
    private:
        TransformComponent* m_transformComponent;
        SDL_Texture* m_texture;
        SDL_Rect m_src;
        SDL_Rect m_dst;

    public:
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        SpriteComponent(const char* textureId) {
            m_texture = Engine::assetManager->GetTexture(textureId);
        }

        ~SpriteComponent() {

        }

        void Initialize() override {
            ASSERT(!(entity->HasComponent<TransformComponent>()), "Sprite component needs a Transform Component on the entity.");
            m_transformComponent = entity->GetComponent<TransformComponent>();
            m_src.x = 0;
            m_src.y = 0;
            m_src.w = m_transformComponent->width;
            m_src.h = m_transformComponent->height;
        }

        void Update(float deltaTime) override {
            m_dst.x = (int) m_transformComponent->position.x;
            m_dst.y = (int) m_transformComponent->position.y;
            m_dst.w = m_transformComponent->width * m_transformComponent->scale;
            m_dst.h = m_transformComponent->height * m_transformComponent->scale;
        }

        void Render() override {
            TextureManager::Draw(m_texture, m_src, m_dst, flip);
        }
};

#endif
