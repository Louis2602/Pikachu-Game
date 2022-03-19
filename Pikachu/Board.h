#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <Windows.h>
#include <vector>
#include "Common.h"

using namespace std;

class Board
{
private:
	static int _size;              // Board size
	static int _left, _top;        // Coordinate to start drawing board
public:
	static void drawBoard(int, int, int);		// Generate Board
	static void addPokemon(int, int, int);
};