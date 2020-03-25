#include "./TestGame.h"

#include "./Engine/Components/TransformComponent.h"
#include "./Engine/Components/SpriteComponent.h"
#include "./Engine/Components/SpriteAnimationComponent.h"
#include "./Engine/Components/BoxColliderComponent.h"
#include "./Engine/Components/TextComponent.h"
#include "./Engine/Components/ProjectileComponent.h"
#include "./Engine/Core/ComponentManager.h"

#include <functional>

TestGame::TestGame() {
    chopper = nullptr;
    chopperAnimation = nullptr;
    chopperTransform = nullptr;
}

void TestGame::Initialize() {
    Game::Initialize();

    int levelNumber = 1;
    std::string levelName = "Level" + std::to_string(levelNumber);
    m_lua.script_file("../assets/scripts/" + levelName + ".lua");
    sol::table levelData = m_lua[levelName];

    /*********************************************/
    /* LOAD ASSETS FROM LUA CONFIG FILE         */
    /*********************************************/
    sol::table levelAssets = levelData["assets"];   
    unsigned int assetIndex = 0;
    while (true) {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex]; 
        if (existsAssetIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                Engine::assetManager->AddTexture(assetId, assetFile.c_str());
            }
            else if (assetType.compare("font") == 0) {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                float fontSize = asset["fontSize"];
                Engine::assetManager->AddFont(assetId, assetFile.c_str(), fontSize);
            } 
        }
        assetIndex++;
    }

    /*********************************************/
    /* LOAD MAP FROM LUA CONFIG FILE            */
    /*********************************************/
    sol::table levelMap = levelData["map"];
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];
    map = new TileMap(
        mapTextureId,
        static_cast<int>(levelMap["scale"]),
        static_cast<int>(levelMap["tileSize"])
    );

    map->LoadData(
        mapFile,
        static_cast<int>(levelMap["mapSizeX"]),
        static_cast<int>(levelMap["mapSizeY"])
    );

    /*********************************************/
    /* LOAD ASSESTS FROM LUA CONFIG FILE         */
    /*********************************************/
    sol::table entityList = levelData["entities"];
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = entityList[entityIndex]; 
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table entity = entityList[entityIndex];
            std::string name = entity["name"];
            LAYER layer = static_cast<LAYER>(static_cast<int>(entity["layer"]));
            auto newEntity(Engine::entityManager->AddEntity(name, layer));
            
            sol::table components = entity["components"];
            unsigned int componentIndex = 0;
            while (true) {
                sol::optional<sol::table> existsComponentIndexNode = components[componentIndex]; 
                if (existsComponentIndexNode == sol::nullopt) {
                    break;
                }
                else {
                    Component* newComponent = ComponentManager::GetComponent(newEntity, components[componentIndex]);
                    if(newComponent!=nullptr) {
                        newEntity->AddComponent(newComponent);
                    }
                }
                componentIndex++;
            }
        }
        entityIndex++;
    }

    inputHor = {0,0};
    inputVert = {0,0};

    chopper = Engine::entityManager->GetEntity("player");
    chopperTransform = chopper->GetComponent<TransformComponent>();
    chopperAnimation = chopper->GetComponent<SpriteAnimationComponent>();

    Engine::collisionManager->RegisterForCollision(chopper, std::bind(&TestGame::OnPlayerCollided, this, std::placeholders::_1));
}

void TestGame::Update(float deltaTime) {
    Engine::cameraManager->SetPos(chopperTransform->position.x - WINDOW_WIDTH/2, chopperTransform->position.y - WINDOW_HEIGHT/2);
}

void TestGame::ProcessInput(SDL_Event event) {
    Game::ProcessInput(event);

    int playerSpeed = 45;

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

    if(chopperAnimation==nullptr)
        return;

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
    //if(entity == projectile) {
        Quit();
    //}
}