#include "./EntityManager.h"

void EntityManager::Update(float deltaTime) {
    for(auto& entity: m_entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for(auto& entity: m_entities) {
        entity->Render();
    }
}

void EntityManager::Clear() {
    for(auto& entity: m_entities) {
        entity->Destroy();
    }
}

Entity& EntityManager::AddEntity(std::string entityId, LAYER layer) {
    Entity* newEntity = new Entity(*this, entityId, layer);
    int entityCount = m_entities.size();
    if(entityCount>0) {
        for(int i=0; i<entityCount; ++i) {
            if(m_entities[i]->GetLayer()>layer) {
                m_entities.insert(m_entities.begin() + i-1, newEntity);
                return *newEntity;
            }
        }
    }

    m_entities.emplace_back(newEntity);
    
    return *newEntity;
}