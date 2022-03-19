#pragma once
#include <Windows.h>
#include <vector>
#include <map>

using namespace std;

class Board
{
private:
	int n_rows, n_cols;
	vector<vector<int>> _pokemons;
public:
	Board(int n_rows, int n_cols, int n_types, vector<int> count);
	int getNRows();
	int getNCols();
	void addPokemon(int x, int y, int type);
	int getPokemon(int x, int y);
	void removePokemon(int x, int y);
};