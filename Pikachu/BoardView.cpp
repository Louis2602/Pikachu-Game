#include "BoardView.h"

BoardView::BoardView(int psize, int pX, int pY) : size(psize), left(pX), top(pY)
{
	pokemons = new int*[size];
	for (int i = 0; i < psize; i++)
		pokemons[i] = new int[size];
	pBoard = new Point * [psize];
	for (int i = 0; i < psize; i++)
		pBoard[i] = new Point[psize];
}

BoardView::~BoardView()
{
	for (int i = 0; i < size; i++)
		delete[] pBoard[i];
	delete[] pBoard,
	pBoard = nullptr;
}

int BoardView::getSize()
{
	return size;
}

int BoardView::getLeft()
{
	return left;
}

int BoardView::getTop()
{
	return top;
}

int BoardView::getXAt(int i, int j)
{
	return pBoard[i][j].getX();
}

int BoardView::getYAt(int i, int j)
{
	return pBoard[i][j].getY();
}

int BoardView::getRAt(int x, int y)
{
	return (y - 2 - top) / 4;
}

int BoardView::getCAt(int x, int y)
{
	return (x - 5 - left) / 8;
}

char BoardView::getPokemons(int x, int y)
{
	return pBoard[getRAt(x,y)][getCAt(x,y)].getPokemons();
}

int BoardView::getCheckAtXY(int pX, int pY)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pBoard[i][j].getX() == pX && pBoard[i][j].getY() == pY)
				return pBoard[i][j].getCheck();
		}
	}
	throw "Problem with cursor position";
}
int BoardView::getCheck(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	return pBoard[r][c].getCheck();
}
/////////////////////////////////////////////////////////////////////
void BoardView::showBoard()
{
	if (pBoard == NULL)
		return;
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();

	// Draw top line
	Controller::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < size * 8; i++)
	{
		Sleep(5);
		if (i % 8 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);
	
	// Draw right line
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(10);
		Controller::gotoXY(size * 8 + left + 1, i + top);
		if (i % 4 != 0)
			putchar(186);
		else
			putchar(182);
	}
	Controller::gotoXY(size * 8 + left + 1, size * 4 + top);
	putchar(188);
	
	// Draw bottom line
	for (int i = 1; i < size * 8; i++)
	{
		Controller::gotoXY(size * 8 + left - i + 1, size * 4 + top);
		Sleep(5);
		if (i % 8 == 0)
			putchar(207);
		else
			putchar(205);
	}
	Controller::gotoXY(left + 1, size * 4 + top);
	putchar(200);
	
	// Draw left line
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(10);
		Controller::gotoXY(left + 1, size * 4 + top - i);
		if (i % 4 != 0)
			putchar(186);
		else
			putchar(199);
	}
	
	// Draw vertical lines
	for (int i = 1; i < size * 4; i++)
	{
		for (int j = 8; j < size * 8; j += 8)
		{
			if (i % 4 != 0)
			{
				Controller::gotoXY(j + left + 1, i + top);
				putchar(179);
			}
		}
		Sleep(10);
	}
	
	// Draw horizontal lines
	for (int i = 1; i < size * 8; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			Controller::gotoXY(i + left + 1, j + top);
			if (i % 8 == 0)
				putchar(197);
			else
				putchar(196);
		}
		Sleep(5);
	}
}

void BoardView::renderBoard() {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pBoard[i][j].setX(8 * j + left + 5); // x-value of boardgame
			pBoard[i][j].setY(4 * i + top + 2); // y-value of boardgame
			pBoard[i][j].setCheck(0);

			int r = pBoard[i][j].getX();
			int c = pBoard[i][j].getY();

			Controller::gotoXY(r, c);
			putchar(pBoard[i][j].getPokemons());
		}
	}
}

void BoardView::buildBoardData() {
	srand((unsigned int)time(NULL));

	bool* checkDuplicate = new bool[size * size];
	int* pos = new int[size * size];

	// Random pokemons
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j+=2) {
			pokemons[i][j] = pokemons[i][j + 1] = rand() % 26 + 'A';
		}
	}

	// Random pokemons position 
	for (int i = 0; i < size * size; i++) 
		checkDuplicate[i] = 0;
	for (int i = 0; i < size * size; i++) {
		int tmp = 0;
		do {
			tmp = rand() % (size * size);
		} while (checkDuplicate[tmp]);
		checkDuplicate[tmp] = 1;
		pos[i] = tmp;
	}

	// Construct pokemons matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int r = pos[size * i + j] / size;
			int c = pos[size * i + j] % size;
			pBoard[i][j].setPokemons(pokemons[r][c]);
		}
	}

	delete[] pos;
	delete[] checkDuplicate;
}

void BoardView::selectedBlock(int x, int y) {
	Controller::setConsoleColor(GREEN, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Controller::gotoXY(j, i);
			putchar(32);
		}
	}
	Controller::gotoXY(x, y);
	putchar(getPokemons(x, y));
	Controller::gotoXY(x, y);
}

void BoardView::unselectedBlock(int x, int y) {
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(_NORMAL);

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Controller::gotoXY(j, i);
			putchar(32);
		}
	}
	Controller::gotoXY(x, y);
	putchar(getPokemons(x, y));
	Controller::gotoXY(x, y);
}

void BoardView::lockBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(_LOCK);

	Controller::setConsoleColor(RED, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Controller::gotoXY(j, i);
			putchar(32);
		}
	}
	Controller::gotoXY(x, y);
	putchar(getPokemons(x, y));
	Controller::gotoXY(x, y);
}

void BoardView::deleteBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(_DELETE);

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 3; j <= x + 3; j++) {
			Controller::gotoXY(j, i);
			putchar(32);
		}
	}
	Controller::gotoXY(x, y);
}