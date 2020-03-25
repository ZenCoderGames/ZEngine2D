#include "./Game.h"

#include "./ComponentManager.h"

void Game::Initialize() {
    m_lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
}

void Game::Start() {
    m_engine = new Engine(this);  
    m_engine->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
    Initialize();
    while (m_engine->IsRunning()) {
        m_engine->ProcessInput();
        m_engine->Update();
        m_engine->Render();
    }
    m_engine->Destroy();
}

void Game::ProcessInput(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                Quit();
            }
        }
        default: {
            break;
        }
    }
}

void Game::Quit() {
    m_engine->Quit();
}

void Game::LoadLua(const char* luaScript, const char* tableName) {
    m_lua.script_file("../assets/scripts/Tetris.lua");
    sol::table levelData = m_lua["Tetris"];

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
            Engine::assetManager->AddAsset(asset);
        }
        assetIndex++;
    }

    /*********************************************/
    /* LOAD ASSETS FROM LUA CONFIG FILE         */
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
            bool isActive = entity["isActive"];
            auto newEntity(Engine::entityManager->AddEntity(name, layer, isActive));

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
}
