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

void BoardView::showBoard()
{
	if (pBoard == NULL)
		return;
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	// Draw top line
	Controller::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(5);
		if (i % 4 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);
	
	// Draw right line
	for (int i = 1; i < size * 2; i++)
	{
		Sleep(10);
		Controller::gotoXY(size * 4 + left + 1, i + top);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(182);
	}
	Controller::gotoXY(size * 4 + left + 1, size * 2 + top);
	putchar(188);
	
	// Draw bottom line
	for (int i = 1; i < size * 4; i++)
	{
		Controller::gotoXY(size * 4 + left - i + 1, size * 2 + top);
		Sleep(5);
		if (i % 4 == 0)
			putchar(207);
		else
			putchar(205);
	}
	Controller::gotoXY(left + 1, size * 2 + top);
	putchar(200);
	
	// Draw left line
	for (int i = 1; i < size * 2; i++)
	{
		Sleep(10);
		Controller::gotoXY(left + 1, size * 2 + top - i);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(199);
	}
	
	// Draw vertical lines
	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				Controller::gotoXY(j + left + 1, i + top);
				putchar(179);
			}
		}
		Sleep(10);
	}
	
	// Draw horizontal lines
	for (int i = 1; i < size * 4; i++)
	{
		for (int j = 2; j < size * 2; j += 2)
		{
			Controller::gotoXY(i + left + 1, j + top);
			if (i % 4 == 0)
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
			pBoard[i][j].setX(4 * j + left + 3); // x-value of boardgame
			pBoard[i][j].setY(2 * i + top + 1); // y-value of boardgame
			pBoard[i][j].setCheck(0);

			Controller::gotoXY(pBoard[i][j].getX(), pBoard[i][j].getY());
			putchar(pBoard[i][j].getPokemons());

		}
	}
}

void BoardView::buildBoardData() {
	//Build random character pair

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			pokemons[i][j] = rand() % 26 + 'A';

			pBoard[i][j].setPokemons(pokemons[i][j]);
		}
	}
}
