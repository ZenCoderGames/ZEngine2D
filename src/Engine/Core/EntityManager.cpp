#include "./EntityManager.h"

void EntityManager::Update(float deltaTime) {
    for(int i=0; i<m_entities.size(); ++i) {
        if(m_entities[i]->IsActive()) {
            m_entities[i]->Update(deltaTime);
        }
    }
}

void EntityManager::Render() {
    for (int layerNumber = 0; layerNumber < TOTAL_LAYERS; ++layerNumber) {
        for (auto& entity: GetEntitiesByLayer(static_cast<LAYER>(layerNumber))) {
            if(entity->IsActive()) {
                entity->Render();
            }
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

Entity* EntityManager::AddEntity(std::string entityId, LAYER layer, bool isActive) {
    Entity* newEntity = new Entity(*this, entityId, layer);
    newEntity->SetActive(isActive);
    m_entities.emplace_back(newEntity);
    m_entityMap.insert(std::pair<std::string,Entity*>(entityId, newEntity));
    return newEntity;
}

void EntityManager::RemoveEntity(Entity *entityToRemove) {
    m_entityMap.erase(entityToRemove->GetId());
    int foundIndex = -1;
    for(int i=0; i<m_entities.size(); ++i) {
        if(entityToRemove == m_entities[i]) {
            entityToRemove->Destroy();
            foundIndex = i;
            break;
        }
    }
    m_entities.erase(m_entities.begin() + foundIndex);
}

Entity* EntityManager::GetEntity(std::string entityId) {
    if(m_entityMap.count(entityId)>0)
        return m_entityMap[entityId];

    return nullptr;
}

Entity* EntityManager::DuplicateEntity(std::string sourceEntityId, std::string newEntityId, bool isActive) {
    Entity* sourceEntity = GetEntity(sourceEntityId);

    Entity* newEntity = new Entity(*this, newEntityId, sourceEntity->GetLayer());
    newEntity->SetActive(isActive);
    m_entities.emplace_back(newEntity);
    m_entityMap.insert(std::pair<std::string,Entity*>(newEntityId, newEntity));

    std::vector<Component*> components = sourceEntity->GetAllComponents();
    for(auto component:components) {
        Component* newComponent = component->clone();
        newEntity->AddComponent(newComponent);
    }

    return newEntity;
}
