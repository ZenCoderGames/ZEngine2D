#include "./Animation.h"

Animation::Animation(std::string name, int index, int totalFrames, float speed) {
    this->name = name;
    this->index = index;
    this->totalFrames = totalFrames;
    this->speed = speed;
}