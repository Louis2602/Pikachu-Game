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
	bool isPause = false;
	printInterface();
	_x = board->getXAt(0, 0);
	_y = board->getYAt(0, 0);
	Controller::gotoXY(_x, _y);
	board->selectedBlock(_x, _y);
	putchar(board->getPokemons(_x, _y));
	Controller::gotoXY(_x, _y);
	while (!isPlaying && _remainBlocks) {
		while (!isPause) {
			switch (Controller::getConsoleInput())
			{
			case 0:
				Controller::playSound(ERROR_SOUND);
				break;
			case 1:
				Menu::exitScreen();
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
				lockBlock();
				break;
			case 7:
				isPause = true;
				Menu::helpScreen();
				break;
			}
		}
		if (isPause)
			continue;
	}
	if(_remainBlocks == 0)
	isPlaying = false;
	_remainBlocks = _mode * _mode;
}

void Game::moveRight()
{
	if (_x < board->getXAt(board->getSize() - 1, board->getSize() - 1))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x += 8;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
	
}

void Game::moveLeft()
{
	if (_x > board->getXAt(0, 0))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_x -= 8;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::moveDown()
{
	if (_y < board->getYAt(board->getSize() - 1, board->getSize() - 1))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y += 4;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::moveUp()
{
	if (_y > board->getYAt(0, 0))
	{
		Controller::playSound(MOVE_SOUND);
		if (board->getCheck(_x, _y) != _LOCK) {
			board->unselectedBlock(_x, _y);
		}

		if (board->getCheckAtXY(_x, _y) == 0)
		{
			Controller::gotoXY(_x, _y);
		}
		_y -= 4;

		if (board->getCheck(_x, _y) != _LOCK) {
			board->selectedBlock(_x, _y);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::printInterface()
{
	board->showBoard();
	board->buildBoardData();
	board->renderBoard();
	Menu::printRectangle(69, 27, 14, 2);
	Menu::printRectangle(88, 27, 14, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(73, 28);
	cout << "H : Help";
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::gotoXY(91, 28);
	cout << "Esc : Exit";
}

char Game::getPokemons(int x, int y)
{
	return board->getPokemons(x, y);
}

void Game::lockBlock()
{
	Controller::playSound(ENTER_SOUND);
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

int Game::checkIMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (firstBlock.first == secondBlock.first && firstBlock.second == secondBlock.second) {
		return 2;
	}
	// check line y -> check value of x
	if (firstBlock.second == secondBlock.second) {
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);

		for (int i = firstBlock.first; i <= secondBlock.first; i += 8) {
			if (i == firstBlock.first || i == secondBlock.first)
				continue;
			if (board->getCheck(i, firstBlock.second) != _DELETE) {
				return 0;
			}
		}
		if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE
			|| board->getCheck(secondBlock.first, secondBlock.second) == _DELETE) {
			return 2;
		}
		if (checkMatchedPokemons(firstBlock,secondBlock))  {
			if (isChecking == false) {
				board->drawLineI(firstBlock, secondBlock);
				Sleep(200);
				board->deleteLineI(firstBlock, secondBlock);
			}
			return 1;
		}
	}
	// check line x -> check value of y
	if (firstBlock.first == secondBlock.first) {
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);

		for (int i = firstBlock.second; i <= secondBlock.second; i += 4) {
			if (i == firstBlock.second || i == secondBlock.second)
				continue;
			if (board->getCheck(firstBlock.first, i) != _DELETE) {
				return 0;
			}
		}
		if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE
			|| board->getCheck(secondBlock.first, secondBlock.second) == _DELETE) {
			return 2;
		}
		if (checkMatchedPokemons(firstBlock, secondBlock)) {
			if (isChecking == false) {
				board->drawLineI(firstBlock, secondBlock);
				Sleep(200);
				board->deleteLineI(firstBlock, secondBlock);
			}
			return 1;
		}
	}
	return 0;
}
bool Game::checkLMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Lcorner;
	Lcorner.first = firstBlock.first;
	Lcorner.second = secondBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == _DELETE) {
		if (checkIMatching(Lcorner, firstBlock, isChecking) && checkIMatching(Lcorner, secondBlock, isChecking)) {
			if (isChecking == false) {
				board->drawLineL(firstBlock, secondBlock, Lcorner);
				Sleep(200);
				board->deleteLineL(firstBlock, secondBlock, Lcorner);
			}
			return 1;
		}
	}

	Lcorner.first = secondBlock.first;
	Lcorner.second = firstBlock.second;
	if (board->getCheck(Lcorner.first, Lcorner.second) == _DELETE) {
		if (checkIMatching(Lcorner, secondBlock, isChecking) && checkIMatching(Lcorner, firstBlock, isChecking)) {
			if (isChecking == false) {
				board->drawLineL(firstBlock, secondBlock, Lcorner);
				Sleep(200);
				board->deleteLineL(firstBlock, secondBlock, Lcorner);
			}
			return 1;
		}	
	}
	return 0;
}
bool Game::checkZMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);

	pair<int, int> Zcorner1;
	pair<int, int> Zcorner2;
	
	for (int i = firstBlock.first + 8; i < secondBlock.first; i += 8) {
		if (board->getCheck(i, firstBlock.second) == _DELETE) {
			if (board->getCheck(i, secondBlock.second) == _DELETE) {
				Zcorner1.first = i;	
				Zcorner1.second = firstBlock.second;
				Zcorner2.first = i;
				Zcorner2.second = secondBlock.second;
				if (checkIMatching(Zcorner1, Zcorner2, isChecking) &&
					checkIMatching(Zcorner2, secondBlock, isChecking)) {
					if (isChecking == false) {
						board->drawLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
						Sleep(200);
						board->deleteLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
					}
					return 1;
				}
			}
		}
		else break;
	}

	if (firstBlock.second > secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second + 4; i < secondBlock.second; i += 4) {
		if (board->getCheck(firstBlock.first, i) == _DELETE) {
			if (board->getCheck(secondBlock.first, i) == _DELETE) {
				Zcorner1.first = firstBlock.first;	
				Zcorner1.second = i;
				Zcorner2.first = secondBlock.first;
				Zcorner2.second = i;
				if (checkIMatching(Zcorner1, Zcorner2, isChecking) &&
					checkIMatching(Zcorner2, secondBlock, isChecking)) {
					if (isChecking == false) {
						board->drawLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
						Sleep(200);
						board->deleteLineZ(firstBlock, secondBlock, Zcorner1, Zcorner2);
					}
					return 1;
				}
			}
		}
		else break;
	}
	return 0;
}
bool Game::checkUMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	pair<int, int> Ucorner1;
	pair<int, int> Ucorner2;
	const int size = board->getSize();
	const int x = board->getXAt(0, 0);
	const int y = board->getYAt(0, 0);
	
	if (firstBlock.first == secondBlock.first)
		if (firstBlock.second > secondBlock.second)
			swap(firstBlock, secondBlock);

	// U ngang trai
	if (firstBlock.first > secondBlock.first)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.first - 8; i >= x - 8; i -= 8) {
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;

		if (i == x - 8) {
			Ucorner1.first = x;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x;
			Ucorner2.second = secondBlock.second;
			if (Ucorner1.first == x && Ucorner2.first == x)
				return 1;
			if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
		}
		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1000);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	// U ngang phai
	if (firstBlock.first < secondBlock.first)
		swap(firstBlock, secondBlock);
	for (int i = secondBlock.first + 8; i <= x + size * 8; i += 8) {
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		
		if (i == x + size * 8) {
			Ucorner1.first = x + size * 8 - 8;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x + size * 8 - 8;
			Ucorner2.second = secondBlock.second;
			if (Ucorner1.first == x + size * 8 - 8 && Ucorner2.first == x + size * 8 - 8)
				return 1;
			if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1000);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	if (firstBlock.second == secondBlock.second)
		if (firstBlock.first > secondBlock.first)
			swap(firstBlock, secondBlock);	

	// U doc tren
	if (firstBlock.second > secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = firstBlock.second - 4; i >= y - 4; i -= 4) {
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;

		if (i == y - 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y;
			if (Ucorner1.second == y && Ucorner2.second == y)
				return 1;
			if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1000);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	// U doc duoi
	if (firstBlock.second < secondBlock.second)
		swap(firstBlock, secondBlock);
	for (int i = secondBlock.second + 4; i <= y + size * 4; i += 4) {
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;

		if (i == y + size * 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y + size * 4 - 4;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y + size * 4 - 4;
			if (Ucorner1.second == y + size * 4 - 4 && Ucorner2.second == y + size * 4 - 4)
				return 1;
			if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1000);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	//}
	return 0;
}
bool Game::checkMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (!checkMatchedPokemons(firstBlock, secondBlock)) {
		return 0;
	}
	if (checkIMatching(firstBlock, secondBlock, isChecking)) {
		return 1;
	}
	if (checkLMatching(firstBlock, secondBlock, isChecking)) {
		return 1;
	}
	if (checkZMatching(firstBlock, secondBlock, isChecking)) {
		return 1;
	}
	if (checkUMatching(firstBlock, secondBlock, isChecking)) {
		return 1;
	}
	return 0;
}

void Game::deleteBlock() {
	_lockedBlock = 0;
	bool isChecking = false;
	if (!checkMatching(_lockedBlockPair[0], _lockedBlockPair[1], isChecking)) {
		for (auto block : _lockedBlockPair)
			board->unselectedBlock(block.first, block.second);
		_lockedBlockPair.clear();
		board->selectedBlock(_x, _y);
		return;
	}
	_remainBlocks -= 2;
	for (auto block : _lockedBlockPair)
		board->deleteBlock(block.first, block.second);
	_lockedBlockPair.clear();
	board->selectedBlock(_x, _y);
	isChecking = true;
	if (!isAvailableBlock(isChecking)) {
		Controller::gotoXY(50, 0);
		cout << "No more ways!!";
	}
	if (_remainBlocks == 0) {
		Controller::gotoXY(40, 0);
		cout << "No more blocks left!! You win the game.";
		board->unselectedBlock(_x, _y);
		_x = board->getXAt(0, 0);
		_y = board->getYAt(0, 0);
		Controller::gotoXY(_x, _y);
		board->selectedBlock(_x, _y);
	}
		
}

bool Game::isAvailableBlock(bool isChecking) {
	int size = board->getSize();
	pair<int, int> firstBlock;
	pair<int, int> secondBlock;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			firstBlock.first = board->getXAt(i, j);
			firstBlock.second = board->getYAt(i, j);
			if (board->getCheck(firstBlock.first, firstBlock.second) == _DELETE) {
				continue;
			}
			for (int m =  i ; m < size; m++) {
				for (int n = 0; n < size; n++) {
					if (i == m && n <= j) continue;
					secondBlock.first = board->getXAt(m, n);
					secondBlock.second = board->getYAt(m, n);
					if(board->getCheck(secondBlock.first, secondBlock.second) == _DELETE)
						continue;
					if (checkMatching(firstBlock, secondBlock, isChecking)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}