#include "./EntityManager.h"

void EntityManager::Update(float deltaTime) {
    for(int i=0; i<m_entities.size(); ++i) {
        m_entities[i]->Update(deltaTime);
        if(!m_entities[i]->IsActive()) {
            m_entityMap.erase(m_entities[i]->GetId());
            m_entities.erase(m_entities.begin() + i);
        }
    }
}

void EntityManager::Render() {
    for (int layerNumber = 0; layerNumber < TOTAL_LAYERS; ++layerNumber) {
        for (auto& entity: GetEntitiesByLayer(static_cast<LAYER>(layerNumber))) {
            entity->Render();
        }
    }
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LAYER layer) const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity: m_entities) {
        if (entity->GetLayer() == layer) {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

void EntityManager::Clear() {
    for(auto& entity: m_entities) {
        entity->Destroy();
    }
    m_entities.clear();
    m_entityMap.clear();
}

Entity& EntityManager::AddEntity(std::string entityId, LAYER layer) {
    Entity* newEntity = new Entity(*this, entityId, layer);
    m_entities.emplace_back(newEntity);
    m_entityMap.insert(std::pair<std::string,Entity*>(entityId, newEntity));
    return *newEntity;
}

Entity* EntityManager::GetEntity(std::string entityId) {
    if(m_entityMap.count(entityId)>0)
        return m_entityMap[entityId];

    return nullptr;
}