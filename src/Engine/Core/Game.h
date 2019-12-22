#ifndef GAME_H
#define GAME_H

#include "../Constants.h"
#include "./Engine.h"
#include "../../../lib/lua/sol.hpp"

class Engine;

class Game {
    protected:
        Engine *m_engine;
        sol::state m_lua;
        virtual void Initialize();
    public:
        void Start();
        virtual void ProcessInput(SDL_Event event);
        virtual void Update(float deltaTime) {}
        void Quit();
};

#endif