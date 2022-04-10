#include "Controller.h"
#include "Game.h"
#include "BoardView.h"
#include "Menu.h"

int main()
{
    Controller::setUpConsole();
    Game g(_EASY);
    g.startGame();
}  