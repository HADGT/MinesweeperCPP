#include "main.h"
#include "funtions.h"
#include "Console.h"
#include <conio.h>

using namespace std;


CauTrucBang CTBang;
CauTrucO** CTO;

/// v? trí con tr? hi?n t?i
COORD CViTriConTro;

//S? d?ng phím
bool BSuDungPhim = false;

// t?a ?? x, y v? b?ng
short SToaDoX;
short SToaDoY;

// c?p nh?t tr?ng thái
bool BTrangThaiChoiGame;

/// <summary>
/// con tr? ??u dòng qu?n lý c? dòng ?ó
/// T?o m?ng 2 chi?u ??ng
/// </summary>
void taoMang2ChieuDong()
{
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}

/// <summary>
/// Xóa hàm ? ??u dòng r?i m?i xóa hàm t?ng
/// xóa m?ng 2 chi?u ??ng
/// </summary>
void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; i++)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
}

void luuToaDoBang()
{
	SToaDoX = ((ConsoleWidth / 2) - CTBang.SDong);
	SToaDoY = (((ConsoleHieght - 6) - CTBang.SCot) / 2) + 6;
}

void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	taoBomNgauNhien();
	luuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	veBang();
	veTrangThaiChoiGame(1, 0, 0);
}

short toaDoX(short SX) // t?a ?? x v? b?ng
{
	return ((SX * 2) + SToaDoX);
}

short toaDoY(short SY) // t?a ?? y v? b?ng
{
	return (SY + SToaDoY);
}

void veO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0: //R?ng màu xanh lá
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 46, (char*)"  ");
		break;
	case 1: //S? 1 ch màu xanh d??ng. T? 1 -> 8 có n?n là màu tr?ng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 25, 15, (char*)"1 ");
		break;
	case 2: //s? 2 xanh lá
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, (char*)"2 ");
		break;
	case 3: //s? 3 ??
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, (char*)"3 ");
		break;
	case 4: //s? 4 xanh d??ng ??m
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, (char*)"4 ");
		break;
	case 5: //s? 5 ?? ??m
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, (char*)"5 ");
		break;
	case 6: //s? 6 CYAN ??m
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, (char*)"6 ");
		break;
	case 7: //s? 7 ?en
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, (char*)"7 ");
		break;
	case 8: //s? 8 h?ng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, (char*)"8 ");
		break;
	case 9: //bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, (char*)"@@");
		break;
	case 10: //ô ch?n
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, (char*)"  ");
		break;
	case 11: //ô l?
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, (char*)"  ");
		break;
	case 12: //theo dõi con tr?
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 13, (char*)"^^");
		break;
	case 13: //c?m c?
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 10, 0, (char*)"!!");
		break;
	case 14: //c?m c? không có bom => c?m c? sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, (char*)"XX");
		break;
	case 15: //c?m c? có bom => c?m c? ?úng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, (char*)"VV");
		break;
	}
}
void veBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
				veO(j, i, 13);
			else if (CTO[i][j].SBomLanCan)
				veO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo) // ô r?ng
				veO(j, i, 0);
			else if ((i + j) % 2) // ô l?
				veO(j, i, 11);
			else // ô ch?n
				veO(j, i, 10);

			if (BSuDungPhim)
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; //SI v? trí dòng, SJ v? trí c?t s? random
	srand(time(NULL));
	while (SSoBom)
	{
		/*công th?c random:
			mu?n random trong kho?ng x, y s? random() % (y - x + 1) + x
			VD kho?ng 0 -> 8 => Ran() % (8 - 0 + 1) + 0 = ran() % 9 = ran() % CTBang.SDong
		*/
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		// ki?m tra v? trí random có bom hay ch?a
		if (CTO[SI][SJ].BCoBom)
			continue;

		CTO[SI][SJ].BCoBom = true;
		--SSoBom; // c?p nh?t l?i s? l??ng bom
	}
}

void xuatBom()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			cout << (int)CTO[i][j].BCoBom << " ";
		}
		cout << endl;
	}
}

void clickPhai(short SX, short SY) // c?m c?
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			// N?u ô này ?ã ???c c?m c?, b? c? ?i
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			// Ki?m tra n?u s? c? còn l?i l?n h?n 0 m?i cho phép c?m c?
			if (CTBang.SSoCo < CTBang.SSoBom)
			{
				CTO[SX][SY].BCamCo = true;
				CTBang.SSoCo++;
			}
			else
			{
				// N?u không còn c? ?? c?m, có th? thêm thông báo ? ?ây n?u mu?n
				// Ví d?: printf("Không còn c? ?? c?m!\n");
			}
		}
	}
	veBang();
	deleteRow(4, 1);
	veTrangThaiChoiGame(1, 0, 0);
}


short demBomLanCan(short SX, short SY)
{
	short SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY + 1; ++j)
		{
			//xét nh?ng v? trí không h?p l? => ti?p t?c l?p
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;

			// xét xem ô có bom hay không, có t?ng ??m lên 1
			if (CTO[i][j].BCoBom)
				++SDem;
		}
	}
	return SDem;
}

void moO(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom)
			thua();
		else
		{
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan) // có bom l?n c?n
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else // ô r?ng
			{
				// duy?t các ô lân c?n và g?i ?? quy
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						//xét nh?ng v? trí không h?p l? => ti?p t?c l?p
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;

						// g?i ?? quy
						moO(i, j);
					}
				}
			}
		}
	}
}

void clickTrai(short SX, short SY) // m? ô
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		moO(SX, SY);
		if (BTrangThaiChoiGame)
		{
			veBang();
			if (thongKeCo())
				thang();
		}
	}
}

bool thongKeCo()
{
	if ((CTBang.SSoODaMo + CTBang.SSoBom) == (CTBang.SDong * CTBang.SCot))
		return true;
	return false;
}

void thang()
{
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong(); // gi?i phóng con tr?
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0);
}

void thua()
{
	// Hi?n bon ?n và ki?m tra c?m c? ?úng hay sai
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo) // có c?m c?
			{
				if (CTO[i][j].BCoBom)
					veO(j, i, 15); // c?m c? ?úng
				else
					veO(j, i, 14); // c?m c? sai
			}
			else // không c?m c?
			{
				if (CTO[i][j].BCoBom) // có bom => hi?n bom
					veO(j, i, 9); // hi?n bom ?n
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong(); // gi?i phóng con tr?
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2, 2, 0); // c?p nh?t l?i tr?ng thái thua
}

/// <summary>
/// ý t??ng x? lý menu
/// s? 1: menu chính
/// s? 2: menu c?p ??
/// s? 3: ?ang ch?i game
/// s? 4: trang thua
/// s? 5: trang th?ng
/// s? 6: trang l?u game
/// </summary>
/// <param name="key"></param>

void xuKienPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown) // có nh?n phím
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP: // m?i tên lên
			switch (STrang)
			{
			case 1:
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2:
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 6:
				veTrangThaiChoiGame(1, 1, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			//cout << "m?i tên lên" << endl;
			break;
		case VK_DOWN: // m?i tên xu?ng
			//cout << "m?i tên xu?ng" << endl;
			switch (STrang)
			{
			case 1:
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2:
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 6:
				veTrangThaiChoiGame(1, 1, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_LEFT: // m?i tên trái
			switch (STrang)
			{
			case 1:
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2:
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 6:
				veTrangThaiChoiGame(1, 1, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			//cout << "m?i tên trái" << endl;
			break;
		case VK_RIGHT: // m?i tên ph?i
			switch (STrang)
			{
			case 1:
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2:
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 6:
				veTrangThaiChoiGame(1, 1, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			//cout << "m?i tên ph?i" << endl;
			break;
		case VK_RETURN: // phím enter
			//cout << "phím enter" << endl;
			switch (STrang)
			{
			case 1:
				if (SViTriChon == 0)
				{
					STrang = 2;
					deleteRow(4, 20);
					veMenuCapDo(0);
				}
				else if (SViTriChon == 1) //trang b?ng ?i?m
				{

				}
				else if (SViTriChon == 2) // trang thông tin
				{
					STrang = 7;
					deleteRow(4, 20);
					veThongTinGame();
				}
				else
				{
					exit(0);
				}
				break;
			case 2:
				if (SViTriChon == 0) // d?
				{
					STrang = 3; // c?p nh?t l?i là ?ang ch?i game
					deleteRow(4, 20);
					khoiTao(9, 9, 10);
				}
				else if (SViTriChon == 1) //trung bình
				{
					STrang = 3; // x?p nh?t l?i là ?ang ch?i game
					deleteRow(4, 20);
					khoiTao(16, 16, 40);
				}
				else if (SViTriChon == 2) // khó
				{
					STrang = 3; // x?p nh?t l?i là ?ang ch?i game
					deleteRow(4, 20);
					khoiTao(24, 24, 99);
				}
				else
				{
					STrang = 1; // c?p nh?t l?i menu chính
					deleteRow(4, 20);
					veMenuChinh(0);
				}
			case 4:
				if (SViTriChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHieght - 3);
					veMenuChinh(0);
				}
				else
				{
					STrang = 3;
					deleteRow(3, ConsoleHieght - 3);
					khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
				}
				break;
			case 5:
				break;
			case 6: // trang l?u game
				if (SViTriChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHieght - 3);
					veMenuChinh(0);
				}
				else
				{
					// l?u game => x? lý file
				}
				break;
			}
			break;
		case VK_ESCAPE: // phím ESC (thoát)
			//cout << "phím ESC (thoát)" << endl;
			switch (STrang)
			{
			case 1:
				exit(0);
			case 2:
				STrang = 1; // c?p nh?t l?i trang menu chính
				deleteRow(4, 20);
				veMenuChinh(0);
				break;
			case 3:
				STrang = 6;
				veTrangThaiChoiGame(1, 1, 1);
				break;
			case 5:
				STrang = 2;
				deleteRow(3, ConsoleHieght - 3);
				veMenuCapDo(0);
				break;
			case 7:
				STrang = 1; // c?p nh?t l?i trang menu chính
				deleteRow(4, 20);
				veMenuChinh(0);
				break;
			}
			break;
		case ClickTrai: // phím z - m? ô
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			//cout << "phím z - m? ô" << endl;
			break;
		case ClickPhai: // phím x - c?m c?
			//cout << "phím x - c?m c?" << endl;
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}

void xuLySuKien()
{
	while (1)
	{
		// l?u l?i s? ki?n hi?n t?i
		DWORD DWNumberOfEvents = 0;
		// l?u l?i s? l??ng s? ki?n ?ã ???c l?c
		DWORD DWNumberOfEventsRead = 0;

		// thi?t b? ?u vào
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		//??t s? ki?n ??u vào c?a giao di?n cho bi?n DWNumberOfEvents
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);

		if (DWNumberOfEvents)
		{
			// con tr? IREventBuffer
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD;
			// ??t các s? ki?n ???c l?u tr? vào con tr? IREventBuffer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);

			// ch?y vòng l?p ?? ??c s? ki?n
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT) // n?u là s? ki?n phím
				{
					xuKienPhim(IREventBuffer[i].Event.KeyEvent);
				}
				else if (IREventBuffer[i].EventType == MOUSE_EVENT) // n?u là s? ki?n chu?t
				{
				}
			}
		}
	}
}

// design

void veTieuDeGame()
{
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}

	setColorBGTextXY((ConsoleWidth / 2) - 12, 1, 5, 0, (char*)"MINESWEEPERS _ NHOM 14\n");
	setColor(7);

	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
	cout << endl;
}

void veTrangThaiChoiGame(short STrangThai, short SCheDo, short Index)
{

	// c?p nh?t l?i v? trí ?ang ch?n và t?ng m?c c?a menu
	SViTriChon = Index;
	STongMuc = 2;

	setColorBGTextXY(1, 3, 15, 0, (char*)"Ban Do: %d * %d", CTBang.SDong, CTBang.SCot);
	setColorBGTextXY(1, 4, 15, 0, (char*)"Ban Bom: %d", CTBang.SSoBom - CTBang.SSoCo);

	//v? menu th?ng thua

	if (SCheDo == 1)
	{
		char StrTextMenuCheDo[] = "  LUU LAI  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuCheDo) / 2) - 2, 3, 15, (Index == 0) ? 2 : 0, (char*)StrTextMenuCheDo);
	}
	if (SCheDo == 2)
	{
		char StrTextMenuCheDo[] = "  CHOI LAI  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuCheDo) / 2) - 1, 3, 15, (Index == 0) ? 2 : 0, (char*)StrTextMenuCheDo);
	}
	if (SCheDo == 3)
	{
		char StrTextMenuCheDo[] = "  LUU TEN  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuCheDo) / 2) - 2, 3, 15, (Index == 0) ? 2 : 0, (char*)StrTextMenuCheDo);
	}
	if (SCheDo >= 1)
	{
		char StrTextMenuCheDo[] = "  THOAT  ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuCheDo) / 2) - 2, 4, 15, (Index == 1) ? 2 : 0, (char*)StrTextMenuCheDo);
	}

	//v? text tr?ng thái
	if (STrangThai == 1) // ?ang ch?i game
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, (char*)"Trang Thai: %s", "Dang choi");
	if (STrangThai == 2) // thua
		setColorBGTextXY(ConsoleWidth - 22, 4, 12, 0, (char*)"Trang Thai: %s", "Thua");
	if (STrangThai == 3) // th?ng
		setColorBGTextXY(ConsoleWidth - 22, 4, 14, 0, (char*)"Trang Thai: %s", "Thang");
	cout << endl;
	setColor(7);
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}

void veMenuChinh(short Index)
{
	// c?p nh?t l?i v? trí ?ang ch?n và t?ng m?c c?a menu
	SViTriChon = Index;
	STongMuc = 4;

	//v? menu
	const char* StrTextMenuChinh1[] = { "  GAME MOI  ", "  BANG DIEM  ", "  THONG TIN  ", "  THOAT  " };

	for (int i = 0; i < STongMuc; ++i)
	{
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuChinh1[i]) / 2), 7 + i, 15, (Index == i) ? 5 : 0, (char*)(StrTextMenuChinh1[i]));
	}
}

void veMenuCapDo(short Index)
{
	// c?p nh?t l?i v? trí ?ang ch?n và t?ng m?c c?a menu
	SViTriChon = Index;
	STongMuc = 4;

	//v? menu
	const char* StrTextMenuCapDo[] = { "  DE (9 * 9 VA 10 BOM) ", "  TRUNG BINH (16 * 16 VA 40 BOM)  ", "  KHO (24 * 24 VA 99 BOM)  ", "  TRO VE  " };
	setColorBGTextXY((ConsoleWidth / 2) - 7, 4, 15, 2, (char*)"  CHON CAP DO  ");
	for (int i = 0; i < STongMuc; ++i)
	{
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuCapDo[i]) / 2), 6 + i, 15, (Index == i) ? 5 : 0, (char*)(StrTextMenuCapDo[i]));
	}
}

void veThongTinGame()
{
	setColorBGTextXY((ConsoleWidth / 2) - 9, 4, 15, 4, (char*)"  HUONG DAN CHOI  ");
	setColorBGTextXY(29, 6, 15, 0, (char*)"  PHIM PG_UP DI LEN  ");
	setColorBGTextXY(29, 7, 15, 0, (char*)"  PHIM PG_DN DI XUONG  ");
	setColorBGTextXY(29, 8, 15, 0, (char*)"  PHIM <HOME DI TRAI  ");
	setColorBGTextXY(29, 9, 15, 0, (char*)"  PHIM END> DI PHAI  ");
	setColorBGTextXY(29, 10, 15, 0, (char*)"  PHIM Z MO O  ");
	setColorBGTextXY(29, 11, 15, 0, (char*)"  PHIM X CAM CO  ");
	setColorBGTextXY(29, 12, 15, 0, (char*)"  PHIM ESC THOAT  ");
}