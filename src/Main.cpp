#include <iostream>
#include "./TestGame.h"

int main(int argc, char *args[]) {
    
    TestGame *game = new TestGame();
    game->Start();

    return 0;
}