#pragma once
#include "Controller.h"
#include "Point.h"
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;


class BoardView {
private:
	int size;						// Size of the board
	int left, top;					// Board Coordinate
	Point** pBoard;					// Board position array
	int* pokemons;
public:
	BoardView(int, int, int);			
	~BoardView();
	int getSize();					//Lấy kích cỡ
	int getLeft();					//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();					//Lấy tọa độ trên bắt đầu bàn cờ
	int getXAt(int, int);			//Lấy tọa độ x tại ô
	int getYAt(int, int);			//Lấy tọa độ y tại ô
	int getCheckAtXY(int, int);

	void showBoard();
	void renderBoard();
	void buildBoardData();
};