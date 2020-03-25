#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../Core/EntityManager.h"
#include "../../../lib/glm/glm.hpp"
#include <SDL.h>
#include "../Core/Engine.h"

class TransformComponent: public Component {
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        float scale;
        float rotation;

        TransformComponent(int posX, int posY, int velX, int velY, float scale=1):Component() {
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX, velY);
            this->scale = scale;
        }

        Component * clone() override {
            TransformComponent* newComponent = new TransformComponent(position.x, position.y, velocity.x, velocity.y, scale);
            return newComponent;
        }

        static TransformComponent* Generate(sol::table paramsTable) {
            TransformComponent* component = new TransformComponent(paramsTable["position"]["x"], 
                                                                    paramsTable["position"]["y"], 
                                                                    0, 0, paramsTable["scale"]);
            return component;
        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
};

#endif
