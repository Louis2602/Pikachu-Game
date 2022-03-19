#pragma once
#ifndef COMMON_H
#define COMMON_H
#include <Windows.h>

class Common {
private:
	static HWND consoleWindow;    //Con trỏ xử lí cửa sổ console
	static HANDLE consoleOutput;  //Con trỏ xử lí output console
public:
	static void gotoXY(int, int);			  //Di chuyển con trỏ đến vị trí x,y
};


#endif 

