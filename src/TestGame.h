#ifndef TEST_GAME_H
#define TEST_GAME_H

#include <iostream>
#include "./Engine/Core/Game.h"
#include "./Engine/Components/TransformComponent.h"
#include "./Engine/Components/SpriteAnimationComponent.h"

class TestGame:public Game {
    protected:
        void Initialize() override;
        void ProcessInput(SDL_Event event) override;
    public:
        Entity *chopper;
        TransformComponent *chopperTransform;
        SpriteAnimationComponent *chopperAnimation;

        TestGame();
};

#endif