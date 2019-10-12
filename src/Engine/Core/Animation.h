#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

class Animation {
    public:
        std::string name;
        unsigned int index;
        unsigned int totalFrames;
        unsigned int speed;

        Animation(std::string name, int index, int totalFrames, int speed);
};

#endif