#include "./Game.h"

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