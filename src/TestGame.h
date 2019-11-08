#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <iostream>
#include "./Engine/Core/Game.h"
#include "./Engine/Components/TransformComponent.h"
#include "./Engine/Components/SpriteAnimationComponent.h"
#include "./Engine/Core/Map.h"

class TestGame:public Game {
    protected:
        void Initialize() override;
    public:
        Map *map;
        Entity *chopper, *tank, *heliport;
        TransformComponent *chopperTransform;
        SpriteAnimationComponent *chopperAnimation;
        glm::vec2 inputHor, inputVert;

        TestGame();

        void ProcessInput(SDL_Event event) override;
        void Update(float deltaTime) override;
        void OnPlayerCollided(Entity* entity);
};

#endif