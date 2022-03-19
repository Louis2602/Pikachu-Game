#pragma once
class Point
{
private:
	int _x;				//Vị trí x
	int _y;				//Vị trí y
	int _check;			//quân cờ trên ô, 1: X, 0: trống, -1: O
public:
	Point();			//Phương thức tạo lập
	Point(int, int);	//Phương thức tạo lập
	int getX();			//Lấy vị trí x
	int getY();			//Lấy vị trí y
	int getCheck();		//Lấy quân cờ
	void setX(int);		//Gán vị trí x
	void setY(int);		//Gán vị trí y
	bool setCheck(int);	//Gán quân cờ
};