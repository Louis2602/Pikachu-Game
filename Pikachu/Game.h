#pragma once
#include "BoardView.h"
#include "Point.h"
#include <iostream>
#include <vector>

#define SIZE 4
#define LEFT 0
#define TOP 0

using namespace std;

class Game {
private:
	BoardView* board;				// Create new board
	int _x, _y;
	bool isPlaying;
public:
	Game();
	~Game();
	void startGame();
	void printInterface();
	void processCheckBoard();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};