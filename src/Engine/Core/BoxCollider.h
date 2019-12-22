#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <string>
#include <SDL.h>

class BoxCollider {
    public:
        std::string tag;
        SDL_Rect rect;
        Entity* parentEntity;

        BoxCollider(std::string tag, int x, int y, int w, int h) {
            this->tag = tag;
            this->rect.x = x;
            this->rect.y = y;
            this->rect.w = w;
            this->rect.h = h;
        }

        void SetPos(int x, int y) {
            this->rect.x = x;
            this->rect.y = y;
        }

        bool IsColliding(SDL_Rect otherRect) {
            return (rect.x + rect.w) >= otherRect.x &&
                (rect.y + rect.h) >= otherRect.y &&
                (otherRect.x + otherRect.w) >= rect.x &&
                (otherRect.y + otherRect.h) >= rect.y;
        }
};

#endif