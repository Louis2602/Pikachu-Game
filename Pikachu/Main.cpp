#include "Controller.h"
#include "BoardView.h"
#include "Game.h"

int main()
{
    Controller::setUpConsole();
    Game g;
    g.startGame();
}