#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL.h>

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;
const float FRAME_MAX_TIME = 0.05f;

enum LAYER {
    LAYER_TILE_MAP,
    LAYER_ENVIRONMENT,
    LAYER_ENEMY,
    LAYER_PLAYER,
    LAYER_UI,
    LAYER_OBSTACLE
};

const unsigned int TOTAL_LAYERS = 6;

const SDL_Color COLOR_WHITE = {255, 255, 255, 255};

#endif