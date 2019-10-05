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

Entity& EntityManager::AddEntity(std::string entityId) {
    Entity* newEntity = new Entity(*this, entityId);
    m_entities.emplace_back(newEntity);
    return *newEntity;
}