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
        std::string m_textureId;
        SDL_Texture* m_texture;
        SDL_Rect m_src;
        SDL_Rect m_dst;
        int m_width;
        int m_height;
        bool m_isFixed;
        bool m_flipX, m_flipY;
        int m_tint[3];
        int m_alpha;
    public:
        SDL_RendererFlip flip = SDL_FLIP_NONE;

        SpriteComponent(std::string textureId, int width, int height, bool isFixed=false, bool flipX=false, bool flipY=false) {
            m_textureId = textureId;
            m_texture = Engine::assetManager->GetTexture(textureId);
            m_width = width;
            m_height = height;
            m_isFixed = isFixed;
            m_flipX = flipX;
            m_flipY = flipY;
            if(flipX)
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
            if(flipY)
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
            m_tint[0] = 255;
            m_tint[1] = 255;
            m_tint[2] = 255;
            m_alpha = 255;
        }

        Component * clone() override {
            SpriteComponent* newComponent = new SpriteComponent(m_textureId, m_width, m_height, m_isFixed, m_flipX, m_flipY);
            newComponent->Tint(m_tint);
            return newComponent;
        }

        static SpriteComponent* Generate(sol::table paramsTable) {
            SpriteComponent* component = new SpriteComponent(paramsTable["textureAssetId"], paramsTable["width"],
                                                             paramsTable["height"], paramsTable["fixed"],
                                                             paramsTable["flipX"], paramsTable["flipY"]);
            sol::optional<sol::table> tintExists = paramsTable["tint"];
            if (tintExists != sol::nullopt) {
                sol::table tint = paramsTable["tint"];
                component->Tint(tint["r"], tint["g"], tint["b"]);
            }
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
            SDL_SetTextureColorMod(m_texture, m_tint[0], m_tint[1], m_tint[2]);
            SDL_SetTextureAlphaMod(m_texture, m_alpha);
            TextureManager::Draw(m_texture, m_src, m_dst, flip);
            SDL_SetTextureColorMod(m_texture, 255, 255, 255);
            SDL_SetTextureAlphaMod(m_texture, 1);
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

        void Tint(int* tint) {
            m_tint[0] = tint[0];
            m_tint[1] = tint[1];
            m_tint[2] = tint[2];
        }

        int* GetTint() {
            return m_tint;
        }

        void Tint(int r, int g, int b) {
            m_tint[0] = r;
            m_tint[1] = g;
            m_tint[2] = b;
        }

        void SetAlpha(int a) {
            m_alpha = a;
        }
};

#endif
