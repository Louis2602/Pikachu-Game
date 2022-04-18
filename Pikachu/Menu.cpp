#include "Menu.h"
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

		 ________  ___  ___  __    ________  ________  ___  ___  ___  ___     
		|\   __  \|\  \|\  \|\  \ |\   __  \|\   ____\|\  \|\  \|\  \|\  \    
		\ \  \|\  \ \  \ \  \/  /|\ \  \|\  \ \  \___|\ \  \\\  \ \  \\\  \   
		 \ \   ____\ \  \ \   __\_ \ \   __  \ \  \    \ \   __  \ \  \\\  \  
		  \ \  \___|\ \  \ \  \\ \  \ \  \ \  \ \  \____\ \  \ \  \ \  \\\  \ 
		   \ \__\    \ \__\ \__\\ \__\ \__\ \__\ \_______\ \__\ \__\ \_______\
		    \|__|     \|__|\|__| \|__|\|__|\|__|\|_______|\|__|\|__|\|_______|                                                                   
	)";
	cout << logo;
	Controller::gotoXY(38, 0);
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	cout << "Tran Tung Lam - Le Minh";
	Controller::gotoXY(40, 1);
	cout << "21127337 - 21127165";
	Controller::gotoXY(38, 8);
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	cout << R"(
  _____  _  _  ___   __  __    _  _____  ___  _  _  ___  _  _   ___    ___    _    __  __  ___ 
 |_   _|| || || __| |  \/  |  /_\|_   _|/ __|| || ||_ _|| \| | / __|  / __|  /_\  |  \/  || __|
   | |  | __ || _|  | |\/| | / _ \ | | | (__ | __ | | | | .` || (_ | | (_ | / _ \ | |\/| || _| 
   |_|  |_||_||___| |_|  |_|/_/ \_\|_|  \___||_||_||___||_|\_| \___|  \___|/_/ \_\|_|  |_||___|
	)";
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
							   54,18,68,18,82,18,18,96,5,24,19,24,33,24,47,24,61,24,75,24,
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
	int line1 = 6, line2 = 19, line3 = 20, line4 = 15;
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
	Controller::gotoXY(left + 1, line4);
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


	Controller::gotoXY(left + 3, top + 8);
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

	Controller::gotoXY(left + 3, top + 15);
	cout << "Scoring:";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 14);
	putchar(249); cout << " I Matching: +1 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 40, top + 14);
	putchar(249); cout << " L Matching: +2 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, GREEN);
	Controller::gotoXY(left1 + 10, top + 15);
	putchar(249); cout << " Z Matching: +3 BTC";
	Controller::gotoXY(left1 + 40, top + 15);
	putchar(249); cout << " U Matching: +4 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 10, top + 16);
	putchar(249); cout << " Not Matched: -2 BTC";
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	Controller::gotoXY(left1 + 40, top + 16);
	putchar(249); cout << " Move suggestion: -2 BTC";

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(left + 3, top + 20);
	cout << "Developers:";
	Controller::gotoXY(left + 31, top + 19);
	cout << "Dev 1: Tran Tung Lam (21127337)";
	Controller::gotoXY(left + 31, top + 21);
	cout << "Dev 2: Le Minh (21127645)";

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

void Menu::leaderBoard()
{
	current_option = 0;
	Controller::clearConsole();
	Player p[100];
	Controller::setConsoleColor(BRIGHT_WHITE, RED);
	cout << R"(
	  _      ______          _____  ______ _____  ____   ____          _____  _____  
	 | |    |  ____|   /\   |  __ \|  ____|  __ \|  _ \ / __ \   /\   |  __ \|  __ \ 
	 | |    | |__     /  \  | |  | | |__  | |__) | |_) | |  | | /  \  | |__) | |  | |
	 | |    |  __|   / /\ \ | |  | |  __| |  _  /|  _ <| |  | |/ /\ \ |  _  /| |  | |
	 | |____| |____ / ____ \| |__| | |____| | \ \| |_) | |__| / ____ \| | \ \| |__| |
	 |______|______/_/    \_\_____/|______|_|  \_\____/ \____/_/    \_\_|  \_\_____/                                                                 
	)";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(5, 8, 85, 17);

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(8, 9);
	cout << "STT";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(13, 8 + i);
		putchar(179);
	}
	for (int i = 6; i < 13; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(18, 9);
	cout << "Name";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(30, 8 + i);
		putchar(179);
	}
	for (int i = 14; i < 30; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(36, 9);
	cout << "ID";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(45, 8 + i);
		putchar(179);
	}
	for (int i = 31; i < 45; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(52, 9);
	cout << "Class";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(62, 8 + i);
		putchar(179);
	}
	for (int i = 46; i < 62; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(68, 9);
	cout << "Mode";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 1; i < 17; i++)
	{
		Controller::gotoXY(78, 8 + i);
		putchar(179);
	}
	for (int i = 63; i < 78; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}

	Controller::setConsoleColor(BRIGHT_WHITE, BLUE);
	Controller::gotoXY(82, 9);
	cout << "Score";
	Controller::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = 79; i < 91; i++)
	{
		Controller::gotoXY(i, 10);
		putchar(196);
	}
	int y = 11;
	int lines = 8;
	int n = 0;
	string tmp;
	fstream fs("rank\\leaderboard.txt", ios::in);

	while (!fs.eof()) {
		getline(fs, p[n].playerName);
		getline(fs, p[n].playerID);
		getline(fs, p[n].className);
		getline(fs, p[n].mode);
		fs >> p[n].score;
		fs.ignore();
		n++;
	}
	fs.close();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (p[j].score > p[i].score) {
				swap(p[i], p[j]);
			}
		}
	}
	for (int i = 1; i < lines; i++) {
		Controller::gotoXY(9, y);
		cout << i;
		Controller::gotoXY(16, y);
		cout << p[i - 1].playerName;
		Controller::gotoXY(33, y);
		cout << p[i - 1].playerID;
		Controller::gotoXY(50, y);
		cout << p[i - 1].className;
		Controller::gotoXY(68, y);
		cout << p[i - 1].mode;
		Controller::gotoXY(84, y);
		cout << p[i - 1].score;
		y += 2;
	}

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
