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
#include "./Sequence/SequenceManager.h"

class EntityManager;
class AssetManager;
class Game;

//////////////////////////////////////////////////////////////////////////////////////////////////
/// This is the core class that runs the game.\n
/// Contains Input->Update->Render in that order.\n
/// Contains all the static managers that are referenced elsewhere.
//////////////////////////////////////////////////////////////////////////////////////////////////
class Engine {
    private:
        bool m_isRunning;
        SDL_Window *m_window;
        Game *m_game;
    public:
        Engine(Game *game);
        ~Engine();

        static EntityManager *entityManager;   /**< Container for all the entities in the game */
        static SDL_Renderer *renderer;
        static AssetManager *assetManager;
        static CameraManager *cameraManager;
        static CollisionManager *collisionManager;
        static SequenceManager *sequenceManager;

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