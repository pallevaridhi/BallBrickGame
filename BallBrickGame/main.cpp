#include <iostream>

#include "BallBrickGame.h"

using namespace std;

int main()
{
    BallBrickGame game_obj;

    game_obj.setWallSize();
    game_obj.displayGame();
    game_obj.setBallCount();

    game_obj.addBricks();
    game_obj.displayGame();
    game_obj.playGame();

    return 0;
}
