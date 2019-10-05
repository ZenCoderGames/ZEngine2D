#ifndef ENTITY_H
#define ENTITY_H

#include "./EntityManager.h"
#include "./Component.h"

#include <vector>
#include <string>

class EntityManager;
class Component;

class Entity {
    private:
        EntityManager& m_Manager;
        std::string m_id;
        bool m_isActive;
        std::vector<Component*> m_components;
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
            newComponent->Initialize();
            return *newComponent;
        }

        template<typename T>
        T* GetComponent() {
            for(auto& component: m_components) {
                T* typedComponent = nullptr;
                if (T* typedComponent = dynamic_cast<T*>(component)) {
                    return (typedComponent);
                }
            }

            return nullptr;
        }
};

#endif