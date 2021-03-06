#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "../Core/AssetManager.h"
#include "../Core/FontManager.h"
#include <SDL_ttf.h>

class TextComponent: public Component {
    private:
        std::string m_fontId;
        TTF_Font* m_font;
        SDL_Rect m_dst;
        SDL_Color m_color;
        std::string m_text;
        SDL_Texture* m_texture;

        void Prepare() {
            SDL_Surface* surface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_color);
            m_texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);
            SDL_FreeSurface(surface);
            SDL_QueryTexture(m_texture, NULL, NULL, &m_dst.w, &m_dst.h);
        }
    public:
        TextComponent(std::string fontId, std::string text, int x, int y, const SDL_Color color) {
            m_fontId = fontId;
            m_font = Engine::assetManager->GetFont(fontId);
            m_text = text;
            m_dst.x = x;
            m_dst.y = y;
            m_color = color;
            Prepare();
        }

        TextComponent * clone() override {
            TextComponent* newComponent = new TextComponent(m_fontId, m_text, m_dst.x, m_dst.y, m_color);
            return newComponent;
        }

        static TextComponent* Generate(sol::table paramsTable) {
            TextComponent* component = new TextComponent(paramsTable["fontId"], paramsTable["text"], paramsTable["posX"], paramsTable["posY"], paramsTable["color"]);
            return component;
        }

        void ModifyFont(std::string fontId) {
            m_font = Engine::assetManager->GetFont(fontId);
            Prepare();
        }

        void ModifyText(std::string text) {
            m_text = text;
            Prepare();
        }

        void Render() override {
            FontManager::Draw(m_texture, m_dst);
        }
};

#endif
