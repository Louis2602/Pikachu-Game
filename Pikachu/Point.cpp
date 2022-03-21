#include "Point.h"

Point::Point()
{
	_x = _y = _check = 0;
}

Point::Point(int x, int y, int check, char pokemon)
{
	_x = x; _y = y;
	_check = check;
	_pokemon = pokemon;
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

void Point::setX(int x)
{
	_x = x;
}

void Point::setY(int y)
{
	_y = y;
}

void Point::setCheck(int check)
{
	_check = check;
}

char Point::getPokemons()
{
	return _pokemon;
}

void Point::setPokemons(char pokemon)
{
	_pokemon = pokemon;
}