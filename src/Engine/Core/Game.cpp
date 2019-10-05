#include "./Game.h"

void Game::Run() {
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
                m_engine->Quit();
            }
        }
        default: {
            break;
        }
    }
}