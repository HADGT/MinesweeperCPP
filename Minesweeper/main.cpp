#include "main.h"
#include "Console.h"
#include "funtions.h"
#include <ctime>

using namespace std;

//Trang, v? tr� ?ang ch?n, t?ng m?c
short STrang, SViTriChon, STongMuc;

int main()
{
	resizeConsole(ConsoleWidth, ConsoleHieght); // thay ??i k�ch th??c m�n console
	SetConsoleTitle(TEXT("Game Do Min")); // ??t ti�u ?? cho game
	veTieuDeGame();
	Cursor(false); // ?n con tr?
	STrang = 1;
	veMenuChinh(0);
	xuLySuKien();
	cout << endl << endl;/*
	system("pause");*/
	return 0;
}