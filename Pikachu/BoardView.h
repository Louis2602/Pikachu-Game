#pragma once
#include "Board.h"
#include "Controller.h"
#include "Point.h"
#include <iostream>

using namespace std;


class BoardView {
private:
	Point** pBoard;
	int size, left, top;
public:
	BoardView(int, int, int);			
	~BoardView();
	int getSize();					//Lấy kích cỡ
	int getLeft();					//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();					//Lấy tọa độ trên bắt đầu bàn cờ
	int getXAt(int, int);			//Lấy tọa độ x tại ô
	int getYAt(int, int);			//Lấy tọa độ y tại ô
	void showBoard();
	int getCheckAtXY(int, int);
};