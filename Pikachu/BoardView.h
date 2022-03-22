﻿#pragma once
#include "Controller.h"
#include "Point.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;


class BoardView {
private:
	int size;						// Size of the board
	int left, top;					// Board Coordinate
	Point** pBoard;					// Board position array
	int** pokemons;
public:
	BoardView(int, int, int);			
	~BoardView();
	int getSize();					//Lấy kích cỡ
	int getLeft();					//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();					//Lấy tọa độ trên bắt đầu bàn cờ
	int getXAt(int, int);			//Lấy tọa độ x tại ô
	int getYAt(int, int);			//Lấy tọa độ y tại ô
	int getCheckAtXY(int, int);
	int getRAt(int, int);			//Lấy tọa độ R (row) tại tọa độ x y
	int getCAt(int, int);			//Lấy tọa độ C (column) tại tọa độ x y
	char getPokemons(int, int);
	int getCheck(int, int);

	void showBoard();
	void renderBoard();
	void buildBoardData();

	void selectedBlock(int, int);
	void unselectedBlock(int, int);
	
	void lockBlock(int, int);
	void deleteBlock(int, int);
};