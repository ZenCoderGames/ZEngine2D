

#include <iostream>
#include "./Tetris/Tetris.h"

int main(int argc, char *args[]) {

    auto *game = new Tetris();
    game->Start();

    return 0;
}