#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "./Entity.h"
#include "../Constants.h"

#include <vector>
#include <string>

class Entity;

class EntityManager {
    private:
        std::vector<Entity*> m_entities;
    public:
        void Update(float deltaTime);
        void Render();
        bool IsEmpty() const { return m_entities.size()==0; }
        void Clear();

        Entity& AddEntity(std::string entityId, LAYER layer);
};

#endif