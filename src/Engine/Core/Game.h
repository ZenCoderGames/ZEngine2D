#ifndef GAME_H
#define GAME_H

#include "../Constants.h"
#include "./Engine.h"

class Engine;

class Game {
    protected:
        Engine *m_engine;
        virtual void Initialize() {};
    public:
        void Start();
        virtual void ProcessInput(SDL_Event event);
        virtual void Update(float deltaTime) {}
        void Quit();
};

#endif