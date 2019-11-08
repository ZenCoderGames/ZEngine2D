#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <SDL2/SDL.h>
#include "../../../lib/glm/glm.hpp"

class CameraManager {
    private:
        SDL_Rect *camera;
        
        void ClampValues() {
            camera->x = camera->x < 0 ? 0: camera->x;
            camera->x = camera->x > camera->w ? camera->w : camera->x;

            camera->y = camera->y < 0 ? 0: camera->y;
            camera->y = camera->y > camera->h ? camera->h : camera->y;
        }

    public:
        CameraManager(int x, int y, int w, int h) {
            camera = new SDL_Rect();
            camera->x = x;
            camera->y = y;
            camera->w = w;
            camera->h = h;
        }
        
        ~CameraManager();

        void SetPos(int x, int y) {
            camera->x = x;
            camera->y = y;
            ClampValues();
        }

        void Move(int x, int y) {
            camera->x += x;
            camera->y += y;
            ClampValues();
        }

        int GetPosX() {
            return camera->x; 
        }

        int GetPosY() {
            return camera->y; 
        }
};

#endif