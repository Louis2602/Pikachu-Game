#include "Game.h"

Game::Game()
{
	_x = LEFT, _y = TOP;
	board = new BoardView(SIZE, LEFT, TOP);
	_loop = true;
	_showCursor = true;
}
Game::~Game() {
	delete board;
	board = nullptr;
}
void Game::startGame() 
{
	Controller::showCursor(_showCursor);
	board->showBoard();
	while (_loop)
	{
		_x = board->getXAt(5, 6);
		_y = board->getYAt(5, 6);
		Controller::gotoXY(_x + 7, _y + 8);		
		
		switch (Controller::getConsoleInput())
		{
		case 2:
			moveUp();
			break;
		case 3:
			moveLeft();
			break;
		case 4:
			moveRight();
			break;
		case 5:
			moveDown();
			break;
		}
	}
}

void Game::moveUp()
{
	if (_y > board->getYAt(0, 0))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
			putchar(32);
		}
		_y -= 2;
		Controller::gotoXY(_x, _y);
	}
}
void Game::moveDown()
{
	if (_y < board->getYAt(board->getSize() - 1, board->getSize() - 1))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
			putchar(32);
		}
		_y += 2;
		Controller::gotoXY(_x, _y);
	}
}
void Game::moveLeft()
{
	if (_x > board->getXAt(0, 0))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
			putchar(32);
		}
		_x -= 4;
		Controller::gotoXY(_x, _y);
	}
}
void Game::moveRight()
{
	if (_x < board->getXAt(board->getSize() - 1, board->getSize() - 1))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
			putchar(32);
		}
		_x += 4;
		Controller::gotoXY(_x, _y);
	}
}