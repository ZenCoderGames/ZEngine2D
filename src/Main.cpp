

#include <iostream>
#include "./Tetris/Tetris.h"
#include "TestGame.h"

int main(int argc, char *args[]) {

    auto *game = new Tetris();
    //auto *game = new TestGame();
    game->Start();

    return 0;
}