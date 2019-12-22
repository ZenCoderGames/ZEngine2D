#ifndef BOX_COLLIDER_COMPONENT_H
#define BOX_COLLIDER_COMPONENT_H

#include "./TransformComponent.h"
#include "../Utils/Macros.h"
#include "../Core/BoxCollider.h"

#include <SDL.h>

class BoxColliderComponent: public Component {
    private:
        TransformComponent* m_transformComponent;
        BoxCollider* m_boxCollider;
        int m_offsetX, m_offsetY;
    public:
        BoxColliderComponent(std::string tag, int offsetX, int offsetY, int w, int h) {
            m_boxCollider = new BoxCollider(tag, 0, 0, w, h);
            m_offsetX = offsetX;
            m_offsetY = offsetY;
        }

        static BoxColliderComponent* Generate(sol::table paramsTable) {
            BoxColliderComponent* component = new BoxColliderComponent(paramsTable["tag"], paramsTable["offsetX"], paramsTable["offsetY"], paramsTable["width"], paramsTable["height"]);
            return component;
        }

        void Initialize() override {
            ASSERT(!(entity->HasComponent<TransformComponent>()), "Collider component needs a Transform Component on the entity.");
            m_transformComponent = entity->GetComponent<TransformComponent>();

            m_boxCollider->parentEntity = entity;
            Engine::collisionManager->RegisterBoxCollider(m_boxCollider);
        }

        void Update(float deltaTime) override {
            m_boxCollider->SetPos(m_transformComponent->position.x + m_offsetX, m_transformComponent->position.y + m_offsetY);
        }

        void Destroy() override {
            Engine::collisionManager->UnregisterBoxCollider(m_boxCollider);
        }
};

#endif
