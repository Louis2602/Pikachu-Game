#include "Board.h"


void Board::drawBoard(int _size, int _left, int _top)
{
	// Draw top line
	Common::gotoXY(_left + 1, _top);
	putchar(201);
	for (int i = 1; i < _size * 4; i++)
	{
		Sleep(5);
		if (i % 4 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);


	// Draw right line
	for (int i = 1; i < _size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(_size * 4 + _left + 1, i + _top);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(182);
	}
	Common::gotoXY(_size * 4 + _left + 1, _size * 2 + _top);
	putchar(188);


	// Draw bottom line
	for (int i = 1; i < _size * 4; i++)
	{
		Common::gotoXY(_size * 4 + _left - i + 1, _size * 2 + _top);
		Sleep(5);
		if (i % 4 == 0)
			putchar(207);
		else
			putchar(205);
	}
	Common::gotoXY(_left + 1, _size * 2 + _top);
	putchar(200);

	// Draw left line
	for (int i = 1; i < _size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(_left + 1, _size * 2 + _top - i);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(199);
	}

	// Draw vertical lines
	for (int i = 1; i < _size * 2; i++)
	{
		for (int j = 4; j < _size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				Common::gotoXY(j + _left + 1, i + _top);
				putchar(179);
			}
		}
		Sleep(10);
	}

	// Draw horizontal lines
	for (int i = 1; i < _size * 4; i++)
	{
		for (int j = 2; j < _size * 2; j += 2)
		{
			Common::gotoXY(i + _left + 1, j + _top);
			if (i % 4 == 0)
				putchar(197);
			else
				putchar(196);
		}
		Sleep(5);
	}
	cout << "\n\n\n\n";
}

void Board::addPokemon(int _size, int _left, int _top) {
	for (int i = 1; i < _size * 2; i++)
	{
		for (int j = 2; j < _size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				Common::gotoXY(j + _left + 1, i + _top);
				char x = rand() % (90-65) + 65;
				putchar(x);
			}
		}
		Sleep(10);
	}
	cout << "\n\n\n\n";
}