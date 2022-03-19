#include "Common.h"

void Common::gotoXY(int pX, int pY)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)pX, (short)pY });
}