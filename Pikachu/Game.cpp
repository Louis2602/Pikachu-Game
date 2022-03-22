#include "Game.h"

Game::Game(int mode)
{
	_mode = mode;
	_x = LEFT, _y = TOP;
	board = new BoardView(_mode, LEFT, TOP);
	isPlaying = false;
	_lockedBlock = 0;
	_lockedBlockPair.clear();
	_remainBlocks = _mode * _mode;
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
	/*Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	putchar(board->getPokemons(0, 0));
	Controller::gotoXY(_x, _y);*/
	board->selectedBlock(_x, _y);
	putchar(board->getPokemons(_x, _y));
	Controller::gotoXY(_x, _y);
	while (!isPlaying && _remainBlocks) {
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
			lockBlock();
			break;
		}
	}
	Controller::setConsoleColor(BLACK, WHITE);
	Controller::clearConsole();
	isPlaying = false;
	_remainBlocks = _mode * _mode;
}

void Game::moveRight()
{
	if (_x < board->getXAt(board->getSize() - 1, board->getSize() - 1))
	{
		//Đổi màu đen cho ô hiện tại
		/*Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(board->getPokemons(_x, _y));
		Controller::gotoXY(_x, _y);*/
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->UnselectedBlock(_x, _y);
		}
		Controller::gotoXY(_x, _y);

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x += 8;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		//Đổi màu xanh cho ô hiện tại
		/*Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
		putchar(board->getPokemons(_x,_y));
		Controller::gotoXY(_x, _y);*/
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
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
		//Đổi màu đen cho ô hiện tại
		/*Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(board->getPokemons(_x, _y));
		Controller::gotoXY(_x, _y);*/
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->UnselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x -= 8;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		//Đổi màu xanh cho ô hiện tại
		//Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
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
		//Đổi màu đen cho ô hiện tại
		/*Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(board->getPokemons(_x, _y));
		Controller::gotoXY(_x, _y);*/
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->UnselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y += 4;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		//Đổi màu xanh cho ô hiện tại
		/*Controller::setConsoleColor(BRIGHT_WHITE, GREEN);*/
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
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
		//Đổi màu đen cho ô hiện tại
		/*Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
		putchar(board->getPokemons(_x, _y));
		Controller::gotoXY(_x, _y);*/
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->UnselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y -= 4;
		Controller::showCursor(true);
		Controller::gotoXY(_x, _y);

		//Đổi màu xanh cho ô hiện tại
		//Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
		if (board->getCheck(_x, _y) != _LOCK && board->getCheck(_x, _y) != _DELETE) {
			board->selectedBlock(_x, _y);
		}
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
	Controller::gotoXY(98, 28);
	cout << "Esc : Exit";
}

char Game::getPokemons(int x, int y)
{
	return board->getPokemons(x, y);
}

void Game::lockBlock()
{
	if (board->getCheck(_x, _y) == _LOCK || board->getCheck(_x, _y) == _DELETE) {
		return;
	}
	board->lockBlock(_x, _y);
	
	_lockedBlockPair.push_back(pair<int, int>(_x, _y));
	_lockedBlock++;

	if (_lockedBlock == 2) {
		deleteBlock();
	}
}

bool Game::checkMatchedPokemons(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	return (board->getPokemons(firstBlock.first, firstBlock.second) == board->getPokemons(secondBlock.first, secondBlock.second));
}

bool Game::checkMatching(pair<int, int> firstBlock, pair<int, int> secondBlock)
{
	if (!checkMatchedPokemons(firstBlock, secondBlock)) 
		return 0;
}
void Game::deleteBlock() {
	_lockedBlock = 0;
	if (!checkMatchedPokemons(_lockedBlockPair[0], _lockedBlockPair[1])) {
		for (auto block : _lockedBlockPair)
			board->UnselectedBlock(block.first, block.second);
		_lockedBlockPair.clear();
		board->selectedBlock(_x, _y);
		return;
	}
	_remainBlocks -= 2;
	for (auto block : _lockedBlockPair)
		board->deleteBlock(block.first, block.second);
	_lockedBlockPair.clear();
}

bool Game::checkWin() {
	if (_remainBlocks == 0)
		return 1;
	return 0;
}