#include "Game.h"

Game::Game()
{
	_x = LEFT, _y = TOP;
	board = new BoardView(SIZE, LEFT, TOP);
	isPlaying = false;
}

Game::~Game() {
	delete board;
	board = nullptr;
}

void Game::startGame() 
{
	Controller::clearConsole();
	isPlaying = false;
	printInterface();	
	_x = board->getXAt(0, 0);
	_y = board->getYAt(0, 0);
	Controller::gotoXY(_x, _y);

	while (!isPlaying) {
		switch (Controller::getConsoleInput())
		{
		case 0:
			Controller::playSound(4);
			break;
		case 1:
			Controller::showCursor(false);
			Controller::setConsoleColor(BLACK, WHITE);
			Controller::clearConsole();
			return;
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
		case 6:
			Controller::playSound(3);
			processCheckBoard();
			break;
		}
	}
}
void Game::processCheckBoard()
{
	
}
void Game::moveRight()
{
	if (_x < board->getXAt(board->getSize() - 1, board->getSize() - 1))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x += 4;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);
	}
	else
	{
		Controller::playSound(4);
	}
}

void Game::moveLeft()
{
	if (_x > board->getXAt(0, 0))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x -= 4;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);
	}
	else
	{
		Controller::playSound(4);
	}
}

void Game::moveDown()
{
	if (_y < board->getYAt(board->getSize() - 1, board->getSize() - 1))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y += 2;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);
	}
	else
	{
		Controller::playSound(4);
	}
}

void Game::moveUp()
{
	if (_y > board->getYAt(0, 0))
	{
		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y -= 2;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);
	}
	else
	{
		Controller::playSound(4);
	}
}

void Game::printInterface()
{
	board->showBoard();
	board->buildBoardData();
	board->renderBoard();
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::gotoXY(91, 28);
	cout << "Esc : Exit";
}