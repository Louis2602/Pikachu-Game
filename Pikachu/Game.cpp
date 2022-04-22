#include "Game.h"

Game::Game(int mode)
{
	_mode = mode;
	_x = LEFT, _y = TOP;
	board = new BoardView(_mode, LEFT, TOP);
	isPlaying = true;
	_lockedBlock = 0;
	_lockedBlockPair.clear();
	_remainBlocks = _mode * _mode;
	score = 0;
}

Game::~Game() {
	delete board;
	board = nullptr;
}

void Game::startGame() 
{
	Controller::clearConsole();
	while (isPlaying) {
		_remainBlocks = _mode * _mode;
		score = 0;
		bool isPause = false;
		printInterface();
		_x = board->getXAt(0, 0);
		_y = board->getYAt(0, 0);
		Controller::gotoXY(_x, _y);
		board->selectedBlock(_x, _y, GREEN);
		putchar(board->getPokemons(_x, _y));
		Controller::gotoXY(_x, _y);
		if (!isAvailableBlock(true)) {
			Controller::setConsoleColor(BRIGHT_WHITE, RED);
			Controller::gotoXY(69, 18);
			cout << "Game Announcement";
			Controller::gotoXY(64, 19);
			cout << "There are no more ways left!";
			Sleep(800);
			Controller::gotoXY(62, 21);
			cout << "Auto reset the board. Have fun!";
			Sleep(1000);
			startGame();
		}
		while (_remainBlocks && !isPause) {
			switch (Controller::getConsoleInput())
			{
			case 0:
				Controller::playSound(ERROR_SOUND);
				break;
			case 1:
				saveData();
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
			case 8:
				moveSuggestion();
				break;
			}
		}
		if (isPause)
			continue;
		askContinue();
	}

	saveData();
}

void Game::setupGame() {
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::clearConsole();
	Controller::gotoXY(0, 0);
	Menu::printLogo();	
	Controller::showCursor(true);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(25, 15);
	cout << "Please enter your name shortly, under 10 characters!";

	Controller::setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
	Controller::gotoXY(35, 18);
	cout << "Enter your name:  ";
	cin.getline(playerName, 15);
	Controller::gotoXY(35, 20);
	cout << "Enter your ID:  ";
	cin.getline(playerID, 9);
	Controller::gotoXY(35, 22);
	cout << "Enter your class's name:  ";
	cin.getline(className, 8);
	if (_mode == 4)
		strcpy_s(mode, "EASY");
	else 
		strcpy_s(mode, "MEDIUM");
	Controller::showCursor(false);
}

void Game::saveData() {
	fstream fs("rank\\leaderboard.txt", ios::app);
	fs << playerName << '\n' << playerID << '\n' << className << '\n' << mode << '\n' << score << '\n';
	fs.close();
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
			board->selectedBlock(_x, _y, GREEN);
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
			board->selectedBlock(_x, _y, GREEN);
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
			board->selectedBlock(_x, _y, GREEN);
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
			board->selectedBlock(_x, _y, GREEN);
		}
	}
	else
		Controller::playSound(ERROR_SOUND);
}

void Game::printInterface()
{
	board->createBackground();
	board->showBoard();
	board->buildBoardData();
	board->renderBoard();

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(59, 1, 33, 10);
	Menu::printRectangle(59, 12, 33, 10);

	Menu::printRectangle(60, 2, 31, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(67, 3);
	cout << "PLAYER'S INFORMATION";

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(65, 5);
	if(strlen(playerName) != 0)
		cout << "Player's name: " << playerName;
	else {
		strcpy_s(playerName, "unknown");
		cout << "Player's name: " << playerName;
	}
	Controller::gotoXY(65, 7);
	if(strlen(playerID) != 0)
		cout << "Student's ID: " << playerID;
	else {
		strcpy_s(playerID, "unknown");
		cout << "Student's ID: " << playerID;
	}
	Controller::gotoXY(65, 9);
	if(strlen(className) != 0)
		cout << "Class: " << className;
	else {
		strcpy_s(className, "unknown");
		cout << "Class: " << className;
	}
	
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(60, 13, 31, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(69, 14);
	cout << "GAME INFORMATION";
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(65, 16);
	cout << "Moves:";
	Controller::gotoXY(65, 17);
	cout << "Current score:";
	Controller::gotoXY(80, 17);
	cout << score;

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(59, 24, 33, 2);
	Menu::printRectangle(59, 27, 14, 2);
	Menu::printRectangle(78, 27, 14, 2);

	Controller::setConsoleColor(BRIGHT_WHITE, PURPLE);
	Controller::gotoXY(67, 25);
	cout << "M : Move suggestion";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(63, 28);
	cout << "H : Help";
	Controller::setConsoleColor(BRIGHT_WHITE, YELLOW);
	Controller::gotoXY(81, 28);
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
			if (Ucorner1.first == firstBlock.first && Ucorner2.first == secondBlock.first)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}
		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
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
	for (int i = firstBlock.first + 8; i <= x + size * 8; i += 8) {
		Ucorner1.first = i;
		Ucorner1.second = firstBlock.second;
		Ucorner2.first = i;
		Ucorner2.second = secondBlock.second;
		
		if (i == x + size * 8) {
			Ucorner1.first = x + size * 8 - 8;
			Ucorner1.second = firstBlock.second;
			Ucorner2.first = x + size * 8 - 8;
			Ucorner2.second = secondBlock.second;

			if (Ucorner1.first == firstBlock.first && Ucorner2.first == secondBlock.first)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(1200);
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

			if (Ucorner1.second == firstBlock.second && Ucorner2.second == secondBlock.second)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE || 
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
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
	for (int i = firstBlock.second + 4; i <= y + size * 4; i += 4) {
		Ucorner1.first = firstBlock.first;
		Ucorner1.second = i;
		Ucorner2.first = secondBlock.first;
		Ucorner2.second = i;

		if (i == y + size * 4) {
			Ucorner2.first = secondBlock.first;
			Ucorner2.second = y + size * 4 - 4;
			Ucorner1.first = firstBlock.first;
			Ucorner1.second = y + size * 4 - 4;

			if (Ucorner1.second == firstBlock.second && Ucorner2.second == secondBlock.second)
				return 1;
			if ((board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE ||
				(Ucorner1.first == firstBlock.first && Ucorner1.second == firstBlock.second))
				&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
				if (checkIMatching(firstBlock, Ucorner1, isChecking) == 2 && checkIMatching(secondBlock, Ucorner2, isChecking) == 2)
					return 1;
			}
			else break;
		}

		if (board->getCheck(Ucorner1.first, Ucorner1.second) == _DELETE
			&& board->getCheck(Ucorner2.first, Ucorner2.second) == _DELETE) {
			if (checkIMatching(Ucorner1, firstBlock, isChecking) == 2 && checkIMatching(Ucorner2, secondBlock, isChecking) == 2
				&& checkIMatching(Ucorner1, Ucorner2, isChecking) == 2) {
				if (isChecking == false) {
					board->drawLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
					Sleep(200);
					board->deleteLineU(firstBlock, secondBlock, Ucorner1, Ucorner2);
				}
				return 1;
			}
		}
		else break;
	}
	return 0;
}
bool Game::checkMatching(pair<int, int> firstBlock, pair<int, int> secondBlock, bool isChecking)
{
	if (!checkMatchedPokemons(firstBlock, secondBlock)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "Not Matched";
			score -= 2;
			Controller::setConsoleColor(BRIGHT_WHITE, RED);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
			}
		}
		return 0;
	}
	if (checkIMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "I Matching.";
			score += 1;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	if (checkLMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "L Matching.";
			score += 2;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	if (checkZMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "Z Matching.";
			score += 3;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
			}
		}
		return 1;
	}
	if (checkUMatching(firstBlock, secondBlock, isChecking)) {
		if (isChecking == false) {
			Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
			Controller::gotoXY(72, 16);
			cout << "U Matching.";
			score += 4;
			Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
			if (score >= 0) {
				Controller::gotoXY(80, 17);
				cout << score << " BTC ";
			}
			else {
				Controller::gotoXY(80, 17);
				cout << score << " BTC";
			}
		}
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
		board->selectedBlock(_x, _y, GREEN);
		return;
	}
	for (auto block : _lockedBlockPair)
		board->deleteBlock(block.first, block.second);
	_lockedBlockPair.clear();
	board->selectedBlock(_x, _y, GREEN);
	_remainBlocks -= 2;
	if (_remainBlocks == 0) {
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(69, 18);
		cout << "Game Announcement";
		Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
		Controller::gotoXY(67, 19);
		cout << "You have won the game.";
		Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
		Controller::gotoXY(69, 20);
		cout << "CONGRATULATIONS!";
		Controller::gotoXY(70, 21);
		cout << "Your score: " << score;
		Controller::playSound(WIN_SOUND);
		board->unselectedBlock(_x, _y);
		_x = board->getXAt(0, 0);
		_y = board->getYAt(0, 0);
		Controller::gotoXY(_x, _y);
		board->selectedBlock(_x, _y, BRIGHT_WHITE);
		Sleep(7000);
		return;
	}
	isChecking = true;
	if (!isAvailableBlock(isChecking)) {
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(69, 18);
		cout << "Game Announcement";
		Controller::gotoXY(64, 19);
		cout << "There are no more ways left!";
		Controller::playSound(EFFECT_SOUND);
		Sleep(1000);
		Controller::gotoXY(62, 21);
		cout << "Auto reset the board. Have fun!";
		Sleep(4000);
		startGame();
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

void Game::askContinue()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	Controller::gotoXY(0, 0);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Menu::printLogo();
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(34, 13, 35, 8);
	Menu::printRectangle(37, 18, 7, 2);
	Menu::printRectangle(60, 18, 6, 2);
	Controller::gotoXY(36, 16);
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	cout << "Do you want to play another round?";
	string str[2] = { "Yes", "No" };
	int left[] = { 35,40,47,58,63,69 }, word[] = { 32,32,175,174 }, color[] = { BLACK, GREEN }, top = 19;
	bool choice = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			Controller::playSound(MOVE_SOUND);
			Controller::setConsoleColor(BRIGHT_WHITE, color[i]);
			Controller::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);
			Controller::gotoXY(left[choice * 3 + 1], top);    cout << str[choice];
			Controller::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]);
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (true)
	{
		int key = Controller::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
			print1();
		else if (key == 6)
		{
			if (!choice)
				isPlaying = true;
			else
				isPlaying = false;
			return;
		}
		else
			Controller::playSound(ERROR_SOUND);
	}
}

void Game::moveSuggestion() {
	bool isHelp = true;
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
			for (int m = i; m < size; m++) {
				for (int n = 0; n < size; n++) {
					if (i == m && n <= j) continue;
					secondBlock.first = board->getXAt(m, n);
					secondBlock.second = board->getYAt(m, n);
					if (board->getCheck(secondBlock.first, secondBlock.second) == _DELETE)
						continue;
					if (checkMatching(firstBlock, secondBlock, isHelp)) {
						if(isHelp) {
							board->selectedBlock(firstBlock.first, firstBlock.second, PURPLE);
							board->selectedBlock(secondBlock.first, secondBlock.second, PURPLE);
							Sleep(200);
							board->unselectedBlock(firstBlock.first, firstBlock.second);
							board->unselectedBlock(secondBlock.first, secondBlock.second);
							score -= 2;
							Controller::setConsoleColor(BRIGHT_WHITE, RED);
							if (score >= 0) {
								Controller::gotoXY(80, 17);
								cout << score << " BTC ";
							}
							else {
								Controller::gotoXY(80, 17);
								cout << score << " BTC";
							}
							return;
						}
					}
				}
			}
		}
	}
}