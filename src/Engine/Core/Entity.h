#ifndef ENTITY_H
#define ENTITY_H

#include "./EntityManager.h"
#include "./Component.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>

class EntityManager;
class Component;

class Entity {
    private:
        EntityManager& m_Manager;
        std::string m_id;
        bool m_isActive;
        std::vector<Component*> m_components;
        std::map<const std::type_info*, Component*> m_componentMap; 
    public:
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string id);

        void Initialize();
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const { return m_isActive; }

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(std::forward<TArgs>(args) ...));
            m_components.emplace_back(newComponent);
            m_componentMap[&typeid(*newComponent)] = newComponent;
            newComponent->entity = this;
            newComponent->Initialize();
            return *newComponent;
        }

        template<typename T>
        T* GetComponent() {
            return static_cast<T*>(m_componentMap[&typeid(T)]);
        }

        template<typename T>
        bool HasComponent() {
            return m_componentMap[&typeid(T)]!=nullptr;
        }
};

#endif