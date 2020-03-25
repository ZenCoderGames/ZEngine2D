#ifndef SPRITE_ANIMATION_COMPONENT_H
#define SPRITE_ANIMATION_COMPONENT_H

#include "../Core/Animation.h"
#include "./SpriteComponent.h"
#include <SDL.h>
#include <map>
#include "../Utils/Macros.h"
#include "../../../lib/json/json.hpp"
#include <fstream>

using json = nlohmann::json;

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
        float m_currentTime;

        int m_totalFrames;
        float m_speed;

        int m_sizeW, m_sizeH;

        struct FrameData {
        public:
            int x, y, w, h;
            int sizeW, sizeH;
            int duration;

            FrameData(json j) {
                json frame = j["frame"];
                x = frame["x"].get<int>();
                y = frame["y"].get<int>();
                w = frame["w"].get<int>();
                h = frame["h"].get<int>();

                json sourceSize = j["sourceSize"];
                sizeW = sourceSize["w"].get<int>();
                sizeH = sourceSize["h"].get<int>();

                duration = j["duration"].get<int>();
            }
        };
        std::vector<FrameData*> m_frameDataList;

        // change later
        std::string m_spriteSheetInfoFile;

    public:
        SpriteAnimationComponent(std::string spriteSheetInfoFile, float animationSpeed, bool loop) {
            m_spriteSheetInfoFile = spriteSheetInfoFile;

            std::ifstream i(spriteSheetInfoFile);
            json j;
            i >> j;

            // Get Frame Data
            json frames = j["frames"];
            for (auto& elem : frames)
                m_frameDataList.push_back(new FrameData(elem));

            // Get Width/Height of File
            json meta = j["meta"];
            json size = meta["size"];
            m_sizeW = size["w"].get<int>();
            m_sizeH = size["h"].get<int>();

            m_speed = animationSpeed;
            m_isLooping = loop;

            Animation *defaultAnimation = new Animation("Default", 0, m_frameDataList.size(), m_speed);
            m_animationMap.emplace(defaultAnimation->name, defaultAnimation);
        }

        Component * clone() override {
            SpriteAnimationComponent* newComponent = new SpriteAnimationComponent(m_spriteSheetInfoFile, m_speed, m_isLooping);
            return newComponent;
        }

        static SpriteAnimationComponent* Generate(sol::table paramsTable) {
            SpriteAnimationComponent* component = new SpriteAnimationComponent(paramsTable["spriteSheetInfoFile"], paramsTable["animationSpeed"], paramsTable["loop"]);
            return component;
        }

        void Initialize() override {
            ASSERT(!(entity->HasComponent<SpriteComponent>()), "Sprite Animation component needs a Sprite Component on the entity.");
            m_spriteComponent = entity->GetComponent<SpriteComponent>();

            m_isPlaying = false;
            m_currentAnim = nullptr;
            m_currentIdx = 0;

            Play(m_isLooping);
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
                int timeInMillisecondsSinceStart = (SDL_GetTicks()-m_animStartTime) * m_currentAnim->speed;
                int frameCount = 0;
                int totalDuration = 0;
                for (auto& frameData : m_frameDataList) {
                    totalDuration += frameData->duration;
                    if(totalDuration>timeInMillisecondsSinceStart) {
                        break;
                    }
                    frameCount++;
                }
                if(frameCount>=m_currentAnim->totalFrames) {
                    if(!m_isLooping) {
                        m_isPlaying = false;
                    }
                    else {
                        m_animStartTime = SDL_GetTicks();
                    }
                }
                else {
                    int x = m_frameDataList[frameCount]->x;
                    int y = m_frameDataList[frameCount]->y;
                    m_spriteComponent->ModifySrcPos(x, y);
                }
            }
        }
};

#endif