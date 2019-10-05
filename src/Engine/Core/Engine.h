#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "./EntityManager.h"
#include "./Game.h"

class EntityManager;
class Game;

class Engine {
    private:
        bool m_isRunning;
        SDL_Window *m_window;
        EntityManager *m_entityManager;
        Game *m_game;
    public:
        Engine(Game *game);
        ~Engine();

        int ticksLastFrame = 0;
        static SDL_Renderer *renderer;
        bool IsRunning() const { return m_isRunning; }

        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
        void Quit() {
            m_isRunning = false;
        }

        EntityManager* GetEntityManager() const { return m_entityManager; }
        Entity& CreateEntity(std::string entityId);
};

#endif