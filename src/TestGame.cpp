#include "./TestGame.h"

#include "./Engine/Components/TransformComponent.h"
#include "./Engine/Components/SpriteComponent.h"

TestGame::TestGame() {
    projectile = nullptr;
}

void TestGame::Initialize() {
    // Load assets
    Engine::assetManager->AddTexture("tank", "./assets/images/tank-big-right.png");

    // Create projectile
    projectile = &(Engine::entityManager->AddEntity("projectile"));
    projectile->AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    projectile->AddComponent<SpriteComponent>("tank");
}

void TestGame::ProcessInput(SDL_Event event) {
    Game::ProcessInput(event);

    switch (event.type) {
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_w) {
                projectile->GetComponent<TransformComponent>()->Modify(12, 12);
            }
            else if (event.key.keysym.sym == SDLK_s) {
                projectile->GetComponent<TransformComponent>()->Modify(32, 32);
            }
        }
        default: {
            break;
        }
    }
}