﻿#include "Menu.h"
#include "Menu.h"
int Menu::current_option;
const string Menu::options[8] = { "Play", "LeaderBoard", "Help", "Exit", "Easy", "  Medium   ", "Back", "Exit"};

void Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], leaderBoard},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], playEasy},
		{options[5], playMedium},
		{options[6], goBack},
		{options[7], exitScreen}
	};
	Controller::playSound(BACKGROUND_SOUND);
	printAnimation();
	bool loadMenu = 1;
	while (true)
	{
		if (loadMenu)
			mainMenu();
		switch (Controller::getConsoleInput())
		{
		case 2:
			changeOption(0, 1);
			loadMenu = 0;
			break;
		case 5:
			changeOption(1, 1);
			loadMenu = 0;
			break;
		case 6:
			if (current_option == 0)
				loadMenu = 0;
			else
				loadMenu = 1;
			function_map[options[current_option]]();
			break;
		default:
			Controller::playSound(ERROR_SOUND);
			loadMenu = 0;
		}
	}

	Controller::clearConsole();
}

void Menu::printLogo()
{
	unsigned char logo[] = R"(
      ___                     ___           ___           ___           ___           ___     
     /  /\      ___          /__/|         /  /\         /  /\         /__/\         /__/\    
    /  /::\    /  /\        |  |:|        /  /::\       /  /:/         \  \:\        \  \:\   
   /  /:/\:\  /  /:/        |  |:|       /  /:/\:\     /  /:/           \__\:\        \  \:\  
  /  /:/~/:/ /__/::\      __|  |:|      /  /:/~/::\   /  /:/  ___   ___ /  /::\   ___  \  \:\ 
 /__/:/ /:/  \__\/\:\__  /__/\_|:|____ /__/:/ /:/\:\ /__/:/  /  /\ /__/\  /:/\:\ /__/\  \__\:\
 \  \:\/:/      \  \:\/\ \  \:\/:::::/ \  \:\/:/__\/ \  \:\ /  /:/ \  \:\/:/__\/ \  \:\ /  /:/
  \  \::/        \__\::/  \  \::/----   \  \::/       \  \:\  /:/   \  \::/       \  \:\  /:/ 
   \  \:\        /__/:/    \  \:\        \  \:\        \  \:\/:/     \  \:\        \  \:\/:/  
    \  \:\       \__\/      \  \:\        \  \:\        \  \::/       \  \:\        \  \::/   
     \__\/                   \__\/         \__\/         \__\/         \__\/         \__\/    
		)";
	cout << logo;
}

void Menu::printOptionsBoard()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 44; //48
	int top = 20;
	Controller::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < 8; i++)
	{
		Controller::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			Controller::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	Controller::gotoXY(left, top + 8);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

void Menu::printAnimation()
{
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	char symbolpos[] = { 5,0,19,0,33,0,47,0,61,0,75,0,89,0,0,103,5,13,19,
							   13,33,13,47,13,61,13,75,13,89,13,13,103,13,18,26,18,40,18,
							   54,18,68,18,82,18,96,18,5,24,19,24,33,24,47,24,61,24,75,24,
							   89,24,24,103,12,30,26,30,40,30,54,30,68,30,82,30,96,30 };
	int n = (sizeof(symbolpos) / sizeof(symbolpos[0])) / 2;
	bool turn = 0;
	unsigned char symbol[] = { 4,15 };

	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };
	int colorcount = 0;
	int loop = 10;
	while (loop--)
	{
		for (int i = 0; i < n; i += 2)
		{
			Controller::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15));
			Controller::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
			putchar(symbol[turn]);
		}
		for (int i = 1; i < n; i += 2)
		{
			Controller::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15));
			Controller::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
			putchar(symbol[!turn]);
		}
		Controller::gotoXY(0, 0);
		printLogo();
		colorcount++;
		turn = !turn;
		Sleep(250);
	}
}

void Menu::changeOption(bool direction, bool flag) //0: lên, 1: xuống
{
	int top = 21;
	if ((direction == 0 && (current_option == 4 || current_option == 0))
		|| (direction == 1 && (current_option == 3 || current_option == 7)))
	{
		Controller::playSound(ERROR_SOUND);
		return;
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::gotoXY(50 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];
	if (flag)
	{
		Controller::gotoXY(40, top + current_option % 4 * 2);
		putchar(32);
		Controller::gotoXY(60, top + current_option % 4 * 2);
		putchar(32);
	}
	(direction == 1) ? current_option++ : current_option--;
	if (flag)
	{
		Controller::playSound(MOVE_SOUND);
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(40, top + current_option % 4 * 2);
		putchar(175);
		Controller::gotoXY(50 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		Controller::gotoXY(60, top + current_option % 4 * 2);
		putchar(174);
	}
}

void Menu::mainMenu()
{
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::clearConsole();
	printLogo();
	printOptionsBoard();
	current_option = 3;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::playMenu()
{
	current_option = 7;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void Menu::helpScreen()
{
	Controller::showCursor(false);
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	int left = 5, top = 2, width = 85, height = 23;
	int line1 = 6, line2 = 19, line3 = 20;
	printRectangle(left, top, width, height);
	Controller::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	Controller::gotoXY(left + 1, line2);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		Controller::gotoXY(line3, top + i);
		putchar(179);
	}
	Controller::gotoXY(line3, line1);
	putchar(197);
	Controller::gotoXY(line3, line2);
	putchar(197);

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 2);
	cout << "Moves:";
	Controller::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Up:    W, up arrow";
	Controller::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Down:  S, down arrow";
	Controller::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Left:  A, left arrow";
	Controller::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Right: D, right arrow";


	Controller::gotoXY(left + 3, top + 10);
	cout << "Rules:";
	Controller::gotoXY(left + 17, top + 5);
	int left1 = left + 17;
	putchar(249); cout << " The Matching Game (commonly known as the Pikachu Puzzle Game)";
	Controller::gotoXY(left1, top + 6);
	cout << " includes a board of multiple cells, each of which presents a figure.";
	Controller::gotoXY(left1, top + 8);
	putchar(249); cout << " The player finds and matches a pair of cells that contain the same";
	Controller::gotoXY(left1, top + 9);
	cout << " figure and connect each other in some particular pattern.";
	Controller::gotoXY(left1, top + 11);
	putchar(249); cout << " A legal match will make the two cells disappear. The game ends when";
	Controller::gotoXY(left1, top + 12);
	cout << " all matching pairs are found.";
	Controller::gotoXY(left1, top + 14);
	putchar(249); cout << " In this project, we will develop a simplified version of this";
	Controller::gotoXY(left1, top + 15);
	cout << " Matching Game by remaking the game with characters (no figures).";

	Controller::gotoXY(left + 3, top + 20);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 19);
	cout << "Student 1: Tran Tung Lam (21127337)";
	Controller::gotoXY(left + 31, top + 21);
	cout << "Student 2: Le Minh (21127645)";

	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(45, 27, 8, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(43, 28);
	putchar(175);
	Controller::gotoXY(48, 28);
	cout << "Back";
	Controller::gotoXY(56, 28);
	putchar(174);
	while (Controller::getConsoleInput() != 6)
	{
		Controller::playSound(ERROR_SOUND);
	}
}

void Menu::printRectangle(int left, int top, int width, int height)
{
	Controller::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (; i < height; i++)
	{
		Controller::gotoXY(left, top + i + 1);
		putchar(179);
		Controller::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Controller::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void Menu::exitScreen()
{
	Controller::showCursor(false);
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Controller::clearConsole();
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	Menu::printRectangle(34, 13, 35, 8);
	Menu::printRectangle(37, 18, 7, 2);
	Menu::printRectangle(60, 18, 6, 2);
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(0, 0);
	printLogo();
	Controller::gotoXY(42, 16);
	cout << "Do you want to exit?";
	string str[2] = { "Yes", "No" };
	int left[] = { 35,40,47,58,63,69 }, word[] = { 32,32,175,174 }, color[] = { BLACK, RED }, top = 19;
	bool choice = 0;
	bool loop = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			Controller::playSound(MOVE_SOUND);
			Controller::setConsoleColor(BRIGHT_WHITE, color[i]);
			Controller::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);
			Controller::gotoXY(left[choice * 3 + 1], top);    cout << str[choice];
			Controller::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]);
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (loop)
	{
		int key = Controller::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
		{
			print1();
		}
		else if (key == 6)
		{
			if (!choice)
			{
				Controller::setConsoleColor(BLACK, BRIGHT_WHITE);
				Controller::clearConsole();
				exit(0);
			}
			return;
		}
		else
		{
			Controller::playSound(ERROR_SOUND);
		}
	}
}

void Menu::playEasy()
{
	Game g(_EASY);
	g.setupGame();
	g.startGame();
}

void Menu::playMedium()
{
	Game g(_MEDIUM);
	g.setupGame();
	g.startGame();
}

void Menu::leaderBoard() {
	Controller::clearConsole();
}
//void Menu::leaderBoard()
//{
//	Controller::clearConsole();
//	vector<string> fileName;
//	for (auto& p : filesystem::recursive_directory_iterator("load"))
//	{
//		if (p.path().extension() == ".txt")
//		{
//			string temp = p.path().filename().string();
//			temp.erase(temp.find_last_of('.'));
//			fileName.push_back(temp);
//		}
//	}
//	if (!fileName.size())
//	{
//		Controller::gotoXY(42, 15);
//		cout << "No game files were found!";
//		Sleep(3000);
//		return;
//	}
//	int file = 8;
//	changeFile(3, fileName, file);
//	bool chosen = 0;
//	while (!chosen)
//	{
//		int key = Controller::getConsoleInput();
//		if (key == 6)
//		{
//			Game g;
//
//			g.startGame();
//			chosen = 1;
//		}
//		else if (key > 1 && key < 6)
//		{
//			changeFile(key, fileName, file);
//		}
//		else if (key == 1)
//		{
//			chosen = 1;
//		}
//		else
//		{
//			Controller::playSound(4);
//		}
//	}
//}

void Menu::changeFile(int key, vector<string>& fileName, int& file)
{
	if (key == 3 || key == 4)
	{
		if (key == 3 && file > 7)
		{
			Controller::playSound(MOVE_SOUND);
			file = (file / 8 - 1) * 8;
		}
		else if (key == 4 && file / 8 < fileName.size() / 8)
		{
			file = (file / 8 + 1) * 8;
		}
		else
		{
			Controller::playSound(ERROR_SOUND);
			return;
		}
		Controller::playSound(MOVE_SOUND);
		Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
		int i = 0;
		for (i = file + 1; i < file + 8; i++)
		{
			Controller::gotoXY(0, 9 + i % 8 * 2);
			for (int j = 0; j < 107; j++)
				putchar(32);
			if (i < fileName.size())
			{
				Controller::gotoXY(54 - fileName[i].find('-'), 9 + i % 8 * 2);
				cout << fileName[i];
			}
		}
		Controller::gotoXY(15, 16);
		(file - 8 < 0) ? putchar(32) : putchar(60);
		Controller::gotoXY(93, 16);
		(file + 8 >= fileName.size()) ? putchar(32) : putchar(62);
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(0, 9);
		for (int j = 0; j < 107; j++)
			putchar(32);
		Controller::gotoXY(54 - fileName[file].find('-'), 9);
		cout << fileName[file];
	}
	else if (key == 2 || key == 5)
	{
		if (key == 2 && file % 8 > 0)
		{
			Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
			Controller::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
			cout << fileName[file];
			file--;
		}
		else if (key == 5 && file % 8 < 7 && file < fileName.size() - 1)
		{
			Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
			Controller::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
			cout << fileName[file];
			file++;
		}
		else
		{
			Controller::playSound(ERROR_SOUND);
			return;
		}
		Controller::setConsoleColor(BRIGHT_WHITE, RED);
		Controller::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
		cout << fileName[file];
	}
}