#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Controller.h"
#include "Game.h"

#define _EASY 4
#define _MEDIUM 6
#define _HARD 8

using namespace std;

struct Menu {
	static void helpScreen();
	static void exitScreen();
	static void printRectangle(int, int, int, int);			//Vẽ hình chữ nhật
};
