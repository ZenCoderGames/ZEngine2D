#include <iostream>
#include "../Constants.h"
#include "./Engine.h"
#include "../../lib/glm/glm.hpp"

#include <string>

EntityManager* Engine::entityManager = new EntityManager();
SDL_Renderer* Engine::renderer;
AssetManager* Engine::assetManager = new AssetManager(entityManager);

Engine::Engine(Game *game):m_game(game) {
    this->m_isRunning = false;
}

void Engine::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!m_window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    m_isRunning = true;
    return;
}

void Engine::ProcessInput() {
    SDL_Event event;
    int eventExists = SDL_PollEvent(&event);
    if(eventExists) {
        switch (event.type) {
            case SDL_QUIT: {
                Quit();
                break;
            }
            default: {
                break;
            }
        }
        m_game->ProcessInput(event);
    }
}

void Engine::Update() {
    // Wait until 16ms has ellapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    
    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > FRAME_MAX_TIME) ? FRAME_MAX_TIME : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    entityManager->Update(deltaTime);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    entityManager->Render();

    SDL_RenderPresent(renderer);
}

void Engine::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}