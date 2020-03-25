//
// Created by srinavinnair on 1/29/20.
//

#ifndef ZCOREENGINE_CELL_H
#define ZCOREENGINE_CELL_H

#include "../Engine/Components/TransformComponent.h"
#include "./TetrisConfig.h"
#include "../Engine/Components/SpriteAnimationComponent.h"

class Cell {
public:
    int r, c;
    Entity* block = nullptr;

    Cell() {}

    Cell(int r, int c) {
        Set(r, c);
    }

    void Set(int r, int c) {
        this->r = r;
        this->c = c;
    }

    void SetBlock(Entity* entity) {
        block = entity;
        block->SetActive(true);
    }

    bool IsEmpty() {
        return block == nullptr;
    }

    void Clear(bool destroyBlock=true) {
        if(block!= nullptr) {
            if(destroyBlock) {
                PlayDestroyEffect();
                block->Destroy();
            }
            block = nullptr;
        }
    }

    void PlayDestroyEffect() {
        Entity *breakEffect = Engine::entityManager->DuplicateEntity("breakAnimation", "breakAnim" + std::to_string(r) + std::to_string(c), true);
        TransformComponent *transformComponent = breakEffect->GetComponent<TransformComponent>();
        transformComponent->position.x = START_X + c * 32;
        transformComponent->position.y = START_Y + r * 32;
        SpriteComponent *blockSprite = block->GetComponent<SpriteComponent>();
        breakEffect->GetComponent<SpriteComponent>()->Tint(blockSprite->GetTint());
    }

    void Draw() {
        if(block != nullptr) {
            TransformComponent *transformComponent = block->GetComponent<TransformComponent>();
            transformComponent->position.x = START_X + c * 32;
            transformComponent->position.y = START_Y + r * 32;
        }
    }
};

#endif //ZCOREENGINE_CELL_H
