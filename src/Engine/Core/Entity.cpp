#include "./Entity.h"

#include <iostream>

Entity::Entity(EntityManager& manager, LAYER layer): m_Manager(manager), m_layer(layer) {
    this->m_isActive = true;
}

Entity::Entity(EntityManager& manager, std::string id, LAYER layer): m_Manager(manager), m_id(id), m_layer(layer) {
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