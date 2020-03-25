#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "./Entity.h"
#include "../Constants.h"

#include <vector>
#include <map>
#include <string>

class Entity;

//////////////////////////////////////////////////////////////////////////////////////////////////
/// This is a container for all entities.
/// Does addition, removal and update for all entities.
//////////////////////////////////////////////////////////////////////////////////////////////////
class EntityManager {
    private:
        std::vector<Entity*> m_entities;
        std::map<std::string, Entity*> m_entityMap;
    public:
        void Update(float deltaTime);
        void Render();
        bool IsEmpty() const { return m_entities.size()==0; }
        void Clear();

        Entity* AddEntity(std::string entityId, LAYER layer, bool isActive=true);
        void RemoveEntity(Entity* entity);
        Entity* GetEntity(std::string entityId);
        std::vector<Entity*> GetEntitiesByLayer(LAYER layer) const;
        Entity* DuplicateEntity(std::string sourceEntityId, std::string newEntityId, bool isActive=true);
};

#endif