#pragma once
#include "BoardView.h"
#include "Point.h"
#include <iostream>
#include <vector>

#define SIZE 4
#define LEFT 25
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
	bool checkIMatching(pair<int, int>, pair<int, int>);
	bool checkLMatching(pair<int, int>, pair<int, int>);
	bool checkZMatching(pair<int, int>, pair<int, int>);
	bool checkUMatching(pair<int, int>, pair<int, int>);
	bool checkMatching(pair<int, int>, pair<int, int>);

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
};