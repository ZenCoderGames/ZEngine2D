#include "./TestGame.h"

#include "./Engine/Components/TransformComponent.h"
#include "./Engine/Components/SpriteComponent.h"
#include "./Engine/Components/SpriteAnimationComponent.h"

TestGame::TestGame() {
    chopper = nullptr;
}

void TestGame::Initialize() {
    // Load assets
    Engine::assetManager->AddTexture("tankImg", "./assets/images/tank-big-right.png");
    Engine::assetManager->AddTexture("chopperImg", "./assets/images/chopper-spritesheet.png");

    // Create tank
    chopper = &(Engine::entityManager->AddEntity("chopper"));
    chopperTransform = &(chopper->AddComponent<TransformComponent>(100, 100, 0, 0, 1));
    chopper->AddComponent<SpriteComponent>("chopperImg", 32, 32);
    chopperAnimation = &(chopper->AddComponent<SpriteAnimationComponent>(2, 90, true));
}

void TestGame::ProcessInput(SDL_Event event) {
    Game::ProcessInput(event);

    switch (event.type) {
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_UP) {
                chopperTransform->velocity.x = 0;
                chopperTransform->velocity.y = -25;
                chopperAnimation->Play("Up");
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                chopperTransform->velocity.x = 0;
                chopperTransform->velocity.y = 25;
                chopperAnimation->Play("Down");
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                chopperTransform->velocity.x = -25;
                chopperTransform->velocity.y = 0;
                chopperAnimation->Play("Left");
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                chopperTransform->velocity.x = 25;
                chopperTransform->velocity.y = 0;
                chopperAnimation->Play("Right");
            }
            break;
        }
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_UP) {
                chopperTransform->velocity.y = 0;
                chopperAnimation->Stop();
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                chopperTransform->velocity.y = 0;
                chopperAnimation->Stop();
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                chopperTransform->velocity.x = 0;
                chopperAnimation->Stop();
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                chopperTransform->velocity.x = 0;
                chopperAnimation->Stop();
            }
            break;
        }
        default: {
            break;
        }
    }
}