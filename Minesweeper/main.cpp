#include "main.h"
#include "Console.h"
#include "funtions.h"
#include <ctime>

using namespace std;

//Trang, vị trí đang chọn, tổng mục
short STrang, SViTriChon, STongMuc;

int main()
{
	resizeConsole(ConsoleWidth, ConsoleHieght); // thay đổi kích thước màn console
	maximizeConsoleWindow();
	SetConsoleTitle(TEXT("Game Do Min")); // đặt tiêu đề cho game
	veTieuDeGame();
	Cursor(false); // ẩn con trỏ
	STrang = 1;
	veMenuChinh(0);
	xuLySuKien();
	cout << endl << endl;
	system("pause");
	return 0;
}