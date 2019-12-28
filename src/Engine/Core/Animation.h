#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

//////////////////////////////////////////////////////////////////////////////////////////////////
/// This is a container for runtime animation.\n
//////////////////////////////////////////////////////////////////////////////////////////////////
class Animation {
    public:
        std::string name;
        unsigned int index;
        unsigned int totalFrames;
        unsigned int speed;

        Animation(std::string name, int index, int totalFrames, int speed);
};

#endif