#include "./TestGame.h"

#include "./Engine/Components/TransformComponent.h"
#include "./Engine/Components/SpriteComponent.h"
#include "./Engine/Components/SpriteAnimationComponent.h"
#include "./Engine/Components/BoxColliderComponent.h"
#include "./Engine/Components/TextComponent.h"

#include <functional>

TestGame::TestGame() {
    chopper = nullptr;
}

void TestGame::Initialize() {
    // Load assets
    Engine::assetManager->AddTexture("tankImg", "./assets/images/tank-big-right.png");
    Engine::assetManager->AddTexture("chopperImg", "./assets/images/chopper-spritesheet.png");
    Engine::assetManager->AddTexture("radarImg", "./assets/images/radar.png");
    Engine::assetManager->AddTexture("jungleMapImg", "./assets/tilemaps/jungle.png");
    Engine::assetManager->AddTexture("heliportImg", "./assets/images/heliport.png");
    Engine::assetManager->AddFont("charriotFont", "./assets/fonts/charriot.ttf", 14);

    // Create map
    map = new Map("jungleMapImg", 2, 32);
    map->LoadData("./assets/tilemaps/jungle.map", 25, 20);

    // Create player
    chopper = &(Engine::entityManager->AddEntity("chopper", LAYER_PLAYER));
    chopperTransform = &(chopper->AddComponent<TransformComponent>(100, 100, 0, 0, 1));
    chopper->AddComponent<SpriteComponent>("chopperImg", 32, 32);
    chopperAnimation = &(chopper->AddComponent<SpriteAnimationComponent>(2, 90, true));
    chopper->AddComponent<BoxColliderComponent>("player", 0, 0, 32, 32);
    //chopper->PrintAllComponents();

    // Create enemy
    tank = &(Engine::entityManager->AddEntity("tank", LAYER_ENEMY));
    TransformComponent *tankTransform = &(tank->AddComponent<TransformComponent>(150, 495, 5, 0, 1));
    tank->AddComponent<SpriteComponent>("tankImg", 32, 32);
    SpriteAnimationComponent *tankAnimation = &(tank->AddComponent<SpriteAnimationComponent>(2, 90, true));
    tank->AddComponent<BoxColliderComponent>("enemy", 0, 0, 32, 32);
    tank->PrintAllComponents();

    // Create radar
    Entity *radar = &(Engine::entityManager->AddEntity("radar", LAYER_UI));
    radar->AddComponent<TransformComponent>(720, 15, 0, 0, 1);
    radar->AddComponent<SpriteComponent>("radarImg", 64, 64, true);
    radar->AddComponent<SpriteAnimationComponent>(8, 150, false).Play(true); 

    // Create heliport
    heliport = &(Engine::entityManager->AddEntity("Heliport", LAYER_OBSTACLE));
    heliport->AddComponent<TransformComponent>(470, 420, 0, 0, 1);
    heliport->AddComponent<SpriteComponent>("heliportImg", 32, 32);
    heliport->AddComponent<BoxColliderComponent>("heliport", 0, 0, 32, 32);

    // Create text
    Entity *testText = &(Engine::entityManager->AddEntity("textTest", LAYER_UI));
    testText->AddComponent<TextComponent>("charriotFont", "Testing...", 10, 10, COLOR_WHITE);

    inputHor = {0,0};
    inputVert = {0,0}; 

    Engine::collisionManager->RegisterForCollision(chopper, std::bind(&TestGame::OnPlayerCollided, *this, std::placeholders::_1));
}

void TestGame::Update(float deltaTime) {
    Engine::cameraManager->SetPos(chopperTransform->position.x - WINDOW_WIDTH/2, chopperTransform->position.y - WINDOW_HEIGHT/2);
}

void TestGame::ProcessInput(SDL_Event event) {
    Game::ProcessInput(event);

    int playerSpeed = 35;

    switch (event.type) {
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_UP) {
                inputVert.x = inputVert.y>0?2:1;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                inputVert.y = inputVert.x>0?2:1;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                inputHor.x = inputHor.y>0?2:1;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                inputHor.y = inputHor.x>0?2:1;
            }
            break;
        }
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_UP) {
                inputVert.x = 0;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                inputVert.y = 0;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                inputHor.x = 0;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                inputHor.y = 0;
            }
            break;
        }
        default: {
            break;
        }
    }

    if(inputHor.x==0 && inputHor.y==0 && inputVert.x==0 && inputVert.y==0) {
        chopperAnimation->Stop();
        chopperTransform->velocity.x = 0;
        chopperTransform->velocity.y = 0;
    }
    else {
        bool isPlayingAnimThisFrame = false;

        if(inputVert.x>0 && inputVert.x>inputVert.y) {
            if(!chopperAnimation->IsPlaying("Up"))
                chopperAnimation->Play("Up", true);

            chopperTransform->velocity.y = -playerSpeed;
            isPlayingAnimThisFrame = true;
        }
        else if(inputVert.y>0 && inputVert.y>inputVert.x) {
            if(!chopperAnimation->IsPlaying("Down"))
                chopperAnimation->Play("Down", true);

            chopperTransform->velocity.y = playerSpeed;
            isPlayingAnimThisFrame = true;
        }
        else if(inputVert.x==0 && inputVert.y==0) {
            chopperTransform->velocity.y = 0;
        }

        if(inputHor.x>0 && inputHor.x>inputHor.y) {
            if(!isPlayingAnimThisFrame && !chopperAnimation->IsPlaying("Left"))
                chopperAnimation->Play("Left", true);

            chopperTransform->velocity.x = -playerSpeed;
        }
        else if(inputHor.y>0 && inputHor.y>inputHor.x) {
            if(!isPlayingAnimThisFrame && !chopperAnimation->IsPlaying("Right"))
                chopperAnimation->Play("Right", true);
 
            chopperTransform->velocity.x = playerSpeed;
        }
        else if(inputHor.x==0 && inputHor.y==0) {
            chopperTransform->velocity.x = 0;
        }
    }
}

void TestGame::OnPlayerCollided(Entity* entity) {
    if(entity == heliport) {
        Quit();
    }
}