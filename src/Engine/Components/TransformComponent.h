#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../Core/EntityManager.h"
#include "../../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Core/Engine.h"

class TransformComponent: public Component {
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        int scale;

        TransformComponent(int posX, int posY, int velX, int velY, int scale) {
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX, velY);
            this->scale = scale;
        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
};

#endif
