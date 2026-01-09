#include "./Game.h"

#include "./ComponentManager.h"
#include <iostream>
#include <filesystem>

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
    // Debug: Print current working directory
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Attempting to load Lua script: " << luaScript << std::endl;

    // Check if file exists
    if (!std::filesystem::exists(luaScript)) {
        std::cerr << "ERROR: Lua script file not found: " << luaScript << std::endl;
        std::cerr << "Current directory: " << std::filesystem::current_path() << std::endl;
        throw std::runtime_error("Lua script file not found");
    }

    try {
        std::cout << "Loading Lua script..." << std::endl;
        m_lua.script_file(luaScript);
        std::cout << "Lua script loaded successfully!" << std::endl;
    } catch (const sol::error& e) {
        std::cerr << "Lua script error: " << e.what() << std::endl;
        std::cerr << "Attempted to load: " << luaScript << std::endl;
        throw;
    }

    std::cout << "Accessing table: " << tableName << std::endl;
    sol::table levelData = m_lua[tableName];

    if (!levelData.valid()) {
        std::cerr << "ERROR: Table '" << tableName << "' not found in Lua script!" << std::endl;
        throw std::runtime_error("Lua table not found");
    }
    std::cout << "Table accessed successfully!" << std::endl;

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
