#ifndef COMPONENT_H
#define COMPONENT_H

#include "./Entity.h"
#include "../../../lib/lua/sol.hpp"

class Entity;

//////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for all components
//////////////////////////////////////////////////////////////////////////////////////////////////
class Component {
    public:
        Entity* entity;

        virtual ~Component() {}
        virtual void Initialize() {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}
        virtual void Destroy() {}

        virtual Component* clone() { return this; }
};

#endif