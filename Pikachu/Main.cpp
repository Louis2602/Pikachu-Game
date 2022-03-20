#include "Controller.h"
#include "Game.h"
#include "BoardView.h"

int main()
{
    Controller::setUpConsole();
    Game g;
    g.startGame();
}  