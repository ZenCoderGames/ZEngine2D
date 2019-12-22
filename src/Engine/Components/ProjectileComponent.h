#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H

#include "./TransformComponent.h"
#include "../../../lib/glm/glm.hpp"

class ProjectileComponent: public Component {
    private:
        TransformComponent* m_transformComponent;
        float m_speed, m_angle, m_range;
        bool m_loop;
        glm::vec2 m_originPos;
    public:
        ProjectileComponent(float speed, float angle, float range, bool loop) {
            m_speed = speed;
            m_angle = glm::radians(angle);
            m_range = range;
            m_loop = loop;
        }

        static ProjectileComponent* Generate(sol::table paramsTable) {
            ProjectileComponent* component = new ProjectileComponent(paramsTable["speed"], paramsTable["angle"], paramsTable["range"], paramsTable["loop"]);
            return component;
        }

        void Initialize() override {
            ASSERT(!(entity->HasComponent<TransformComponent>()), "Projectile component needs a Transform Component on the entity.");
            m_transformComponent = entity->GetComponent<TransformComponent>();

            m_originPos = glm::vec2(m_transformComponent->position.x, m_transformComponent->position.y);
            m_transformComponent->velocity = glm::vec2(m_speed * glm::cos(m_angle), m_speed * glm::sin(m_angle));
        }

        void Update(float deltaTime) override {
           if(glm::distance(m_transformComponent->position, m_originPos)>m_range) {
               if(m_loop) {
                   m_transformComponent->position.x = m_originPos.x;
                   m_transformComponent->position.y = m_originPos.y;
               }
               else {
                   entity->Destroy();
               }
           }   
            
        }
};

#endif