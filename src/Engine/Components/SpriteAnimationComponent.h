#ifndef SPRITE_ANIMATION_COMPONENT_H
#define SPRITE_ANIMATION_COMPONENT_H

#include "../Core/Animation.h"
#include "./SpriteComponent.h"
#include <SDL2/SDL.h>
#include <map>

class SpriteAnimationComponent: public Component {
    private:
        SpriteComponent* m_spriteComponent;

        std::map<std::string, Animation*> m_animationMap;
        std::string m_animGroupName;
        Animation* m_currentAnim;
        unsigned int m_currentIdx;
        bool m_animate;
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

            m_animate = false;
            m_currentIdx = 0;
        }

        void Play() {
            m_currentAnim = m_animationMap["Default"];
            m_animate = true;
        }

        void Play(std::string animName) {
            m_currentAnim = m_animationMap[animName];
            m_currentIdx = m_currentAnim->index;
            m_animate = true;
        }

        void Stop() {
            m_animate = false;
        }

        void Update(float deltaTime) override {
            if(m_animate) {
                int x = m_spriteComponent->GetWidth() * static_cast<int>((SDL_GetTicks() / m_currentAnim->speed) % m_currentAnim->totalFrames);
                int y = m_currentIdx * m_spriteComponent->GetHeight();
                m_spriteComponent->ModifySrcPos(x, y);
            }
        }
};

#endif