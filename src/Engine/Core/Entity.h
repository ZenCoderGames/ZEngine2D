#ifndef ENTITY_H
#define ENTITY_H

#include "./EntityManager.h"
#include "./Component.h"
#include "../Constants.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>

class EntityManager;
class Component;

//////////////////////////////////////////////////////////////////////////////////////////////////
/// This class represents actual objects in the game.
/// By itself it is just an id but it is the components that define its behavior
//////////////////////////////////////////////////////////////////////////////////////////////////
class Entity {
    private:
        EntityManager& m_Manager;
        std::string m_id;
        bool m_isActive;
        std::vector<Component*> m_components;
        std::map<const std::type_info*, Component*> m_componentMap;
        LAYER m_layer;
    public:
        Entity(EntityManager& manager, LAYER layer);
        Entity(EntityManager& manager, std::string id, LAYER layer);

        void Initialize();
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const { return m_isActive; }
        void SetActive(bool val) { m_isActive = val; }
        LAYER GetLayer() const { return m_layer; }
        std::string GetId() { return m_id; }

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* newComponent(new T(std::forward<TArgs>(args) ...));
            m_components.emplace_back(newComponent);
            m_componentMap[&typeid(*newComponent)] = newComponent;
            newComponent->entity = this;
            newComponent->Initialize();
            return *newComponent;
        }

        void AddComponent(Component* newComponent) {
            m_components.emplace_back(newComponent);
            m_componentMap[&typeid(*newComponent)] = newComponent;
            newComponent->entity = this;
            newComponent->Initialize();
        }

        template<typename T>
        T* GetComponent() {
            return static_cast<T*>(m_componentMap[&typeid(T)]);
        }

        template<typename T>
        bool HasComponent() {
            return m_componentMap[&typeid(T)]!=nullptr;
        }

        std::vector<Component*> GetAllComponents() const {
            return m_components;
        }

        void PrintAllComponents() const {
            std::cout<<"Components:"<<std::endl;
            for(auto component: m_componentMap) {
                std::cout<<component.first->name() << std::endl;
            }
        }
};

#endif