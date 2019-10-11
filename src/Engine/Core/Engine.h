#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "./EntityManager.h"
#include "./AssetManager.h"
#include "./Game.h"

class EntityManager;
class AssetManager;
class Game;

class Engine {
    private:
        bool m_isRunning;
        SDL_Window *m_window;
        Game *m_game;
    public:
        Engine(Game *game);
        ~Engine();

        static EntityManager *entityManager;
        static SDL_Renderer *renderer;
        static AssetManager *assetManager;

        int ticksLastFrame = 0;
        bool IsRunning() const { return m_isRunning; }

        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
        void Quit() {
            m_isRunning = false;
        }
};

#endif