#include "Point.h"

Point::Point()
{
	_x = _y = _check = 0;
}

Point::Point(int pX, int pY)
{
	_x = pX; _y = pY;
	_check = 0;
}

int Point::getX()
{
	return _x;
}

int Point::getY()
{
	return _y;
}

int Point::getCheck()
{
	return _check;
}

void Point::setX(int pX)
{
	_x = pX;
}

void Point::setY(int pY)
{
	_y = pY;
}

bool Point::setCheck(int pCheck)
{
	if (pCheck == -1 || pCheck == 1 || pCheck == 0)
	{
		_check = pCheck;
		return true;
	}
	return false;
}
