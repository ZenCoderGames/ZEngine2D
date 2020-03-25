#ifndef GAME_H
#define GAME_H

#include "../Constants.h"
#include "./Engine.h"
#include "../../../lib/lua/sol.hpp"

class Engine;

//////////////////////////////////////////////////////////////////////////////////////////////////
/// This is a base class that is called by the engine loop.
/// New game modes will inherit and override properties of this class.
//////////////////////////////////////////////////////////////////////////////////////////////////
class Game {
    protected:
        Engine *m_engine;
        sol::state m_lua;
        virtual void Initialize();
    public:
        void Start();
        void LoadLua(const char* luaScript, const char* tableName);
        virtual void ProcessInput(SDL_Event event);
        virtual void Update(float deltaTime) {}
        void Quit();
};

#endif