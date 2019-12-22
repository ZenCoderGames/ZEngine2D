#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "./EntityManager.h"
#include "./AssetManager.h"
#include "./Game.h"
#include "./CameraManager.h"
#include "./CollisionManager.h"

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
        static CameraManager *cameraManager;
        static CollisionManager *collisionManager;

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