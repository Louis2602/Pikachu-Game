#pragma once
#include "BoardView.h"
#include "Point.h"
#include <iostream>

using namespace std;
#define SIZE 14
#define LEFT 4
#define TOP 1

class Game {
private:
	BoardView* board; // Create new board
	int _x, _y;
	bool _loop;
	bool _showCursor;
public:
	Game();
	~Game();
	void startGame();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};