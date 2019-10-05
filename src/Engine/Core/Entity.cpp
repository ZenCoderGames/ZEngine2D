#include "./Entity.h"

Entity::Entity(EntityManager& manager): m_Manager(manager) {
    this->m_isActive = true;
}

Entity::Entity(EntityManager& manager, std::string id): m_Manager(manager), m_id(id) {
    this->m_isActive = true;
}

void Entity::Update(float deltaTime) {
    for(auto& component: m_components)
        component->Update(deltaTime);
}

void Entity::Render() {
    for(auto& component: m_components)
        component->Render();
}

void Entity::Destroy() {
    this->m_isActive = false;
}