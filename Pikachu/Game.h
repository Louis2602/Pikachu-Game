#pragma once
#include "BoardView.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include "Menu.h"

#define LEFT 5
#define TOP 1

using namespace std;

struct Game {
	BoardView* board;				// Create new board
	int _mode;
	int _x, _y;
	bool isPlaying;
	int _lockedBlock;
	int _remainBlocks;

	vector<pair<int, int>> _lockedBlockPair; //First: row - Second: column

	bool checkMatchedPokemons(pair<int, int>, pair<int, int>);
	int checkIMatching(pair<int, int>, pair<int, int>, bool);
	bool checkLMatching(pair<int, int>, pair<int, int>, bool);
	bool checkZMatching(pair<int, int>, pair<int, int>, bool);
	bool checkUMatching(pair<int, int>, pair<int, int>, bool);
	bool checkMatching(pair<int, int>, pair<int, int>, bool);

	Game(int);
	~Game();

	void startGame();
	void printInterface();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	char getPokemons(int x, int y);

	void lockBlock();
	void deleteBlock();
	bool isAvailableBlock(bool);
};