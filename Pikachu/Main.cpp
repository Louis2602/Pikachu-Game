#include "Controller.h"
#include "Game.h"
#include "BoardView.h"


#define _EASY 4
#define _MEDIUM 6
#define _HARD 8

int main()
{
    Controller::setUpConsole();
    Game g(_EASY);
    g.startGame();
}  