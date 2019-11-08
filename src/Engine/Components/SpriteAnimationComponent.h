#ifndef SPRITE_ANIMATION_COMPONENT_H
#define SPRITE_ANIMATION_COMPONENT_H

#include "../Core/Animation.h"
#include "./SpriteComponent.h"
#include <SDL2/SDL.h>
#include <map>
#include "../Utils/Macros.h"

class SpriteAnimationComponent: public Component {
    private:
        SpriteComponent* m_spriteComponent;

        std::map<std::string, Animation*> m_animationMap;
        std::string m_animGroupName;
        Animation* m_currentAnim;
        unsigned int m_currentIdx;
        bool m_isPlaying;
        bool m_isLooping;
        Uint32 m_animStartTime;
    public:
        SpriteAnimationComponent(int totalFrames, int speed, bool isDirectional=false) {
            if(isDirectional) {
                Animation *downAnimation = new Animation("Down", 0, totalFrames, speed);
                Animation *rightAnimation = new Animation("Right", 1, totalFrames, speed);
                Animation *leftAnimation = new Animation("Left", 2, totalFrames, speed);
                Animation *upAnimation = new Animation("Up", 3, totalFrames, speed);
                m_animationMap.emplace(downAnimation->name, downAnimation);
                m_animationMap.emplace(rightAnimation->name, rightAnimation);
                m_animationMap.emplace(leftAnimation->name, leftAnimation);
                m_animationMap.emplace(upAnimation->name, upAnimation);
            }
            else {
                Animation *defaultAnimation = new Animation("Default", 0, totalFrames, speed);
                m_animationMap.emplace(defaultAnimation->name, defaultAnimation);
            }
        }

        void Initialize() override {
            ASSERT(!(entity->HasComponent<SpriteComponent>()), "Sprite Animation component needs a Sprite Component on the entity.");
            m_spriteComponent = entity->GetComponent<SpriteComponent>();

            m_isPlaying = false;
            m_currentAnim = nullptr;
            m_currentIdx = 0;
        }

        void Play(bool isLooping) {
            m_currentAnim = m_animationMap["Default"];
            m_isPlaying = true;
            m_isLooping = isLooping;
            m_animStartTime = SDL_GetTicks();
        }

        void Play(std::string animName, bool isLooping) {
            m_currentAnim = m_animationMap[animName];
            ASSERT(m_currentAnim==nullptr, STR_CONCAT("Invalid anim id: ", animName));
            m_currentIdx = m_currentAnim->index;
            m_isPlaying = true;
            m_isLooping = isLooping;
            m_animStartTime = SDL_GetTicks();
        }

        bool IsPlaying() {
            return m_isPlaying;
        }

        bool IsPlaying(std::string animName) {
            return m_currentAnim!=nullptr && m_currentAnim->name == animName && m_isPlaying;
        }

        void Stop() {
            m_isPlaying = false;
        }

        void Update(float deltaTime) override {
            if(m_isPlaying) {
                int frameCount = (SDL_GetTicks()-m_animStartTime) / m_currentAnim->speed;
                // horizontal represents the animated frames
                int x = m_spriteComponent->GetWidth() * static_cast<int>(frameCount % m_currentAnim->totalFrames);

                // vertical represents the section of the sprite sheet
                int y = m_currentIdx * m_spriteComponent->GetHeight();
                m_spriteComponent->ModifySrcPos(x, y);

                if(!m_isLooping) {
                    if(frameCount>=m_currentAnim->totalFrames) {
                        m_isPlaying = false;
                    }
                }
            }
        }
};

#endif