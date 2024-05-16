#include "main.h"
#include "funtions.h"
#include "Console.h"
#include <conio.h>
#include <windows.h> 

using namespace std;


CauTrucBang CTBang;
CauTrucO** CTO;

/// vị trí con trỏ hiện tại
COORD CViTriConTro;

//Sử dụng phím
bool BSuDungPhim = false;

// tọa độ x, y vẽ bảng
short SToaDoX;
short SToaDoY;

// cập nhật trạng thái
bool BTrangThaiChoiGame;

/// <summary>
/// con trỏ đầu dòng quản lý cả dòng đó
/// Tạo mảng 2 chiều động
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
/// Xóa hàm ở đầu dòng rồi mới xóa hàm tổng
/// xóa mảng 2 chiều động
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

short toaDoX(short SX) // tọa độ x vẽ bảng
{
	return ((SX * 2) + SToaDoX);
}

short toaDoY(short SY) // tọa độ y vẽ bảng
{
	return (SY + SToaDoY);
}

void veO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0: //Rỗng màu xanh lá
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, (char*)"  ");
		break;
	case 1: //Số 1 ch màu xanh dương. Từ 1 -> 8 có nền là màu trắng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, (char*)"1 ");
		break;
	case 2: //số 2 xanh lá
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, (char*)"2 ");
		break;
	case 3: //số 3 đỏ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, (char*)"3 ");
		break;
	case 4: //số 4 xanh dương đậm
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, (char*)"4 ");
		break;
	case 5: //số 5 đỏ đậm
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, (char*)"5 ");
		break;
	case 6: //số 6 CYAN đậm
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, (char*)"6 ");
		break;
	case 7: //số 7 đen
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, (char*)"7 ");
		break;
	case 8: //số 8 hồng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, (char*)"8 ");
		break;
	case 9: //bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, (char*)"* ");
		break;
	case 10: //ô chẵn
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, (char*)"  ");
		break;
	case 11: //ô lẻ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, (char*)"  ");
		break;
	case 12: //theo dõi con trỏ
		setColorBGTextXY(toaDoX(SX) + 1, toaDoY(SY), 0, 13, (char*)" ");
		break;
	case 13: //cắm cờ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, (char*)"P ");
		break;
	case 14: //cắm cờ không có bom => cắm cờ sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, (char*)"Px");
		break;
	case 15: //cắm cờ có bom => cắm cờ đúng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, (char*)"B ");
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
			else if (CTO[i][j].BDaMo) // ô rỗng
				veO(j, i, 0);
			else if ((i + j) % 2) // ô lẻ
				veO(j, i, 11);
			else // ô chẵn
				veO(j, i, 10);

			if (BSuDungPhim)
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; //SI vị trí dòng, SJ vị trí cột sẽ random
	srand(time(NULL));
	while (SSoBom)
	{
		/*công thức random:
			muốn random trong khoảng x, y sẽ random() % (y - x + 1) + x
			VD khoảng 0 -> 8 => Ran() % (8 - 0 + 1) + 0 = ran() % 9 = ran() % CTBang.SDong
		*/
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		// kiểm tra vị trí random có bom hay chưa
		if (CTO[SI][SJ].BCoBom)
			continue;

		CTO[SI][SJ].BCoBom = true;
		--SSoBom; // cập nhật lại số lượng bom
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

void clickPhai(short SX, short SY) // cắm cờ
{
	if (!CTO[SX][SY].BDaMo)
	{
		if (CTO[SX][SY].BCamCo)
		{
			// Nếu ô này đã được cắm cờ, bỏ cờ đi
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			// Kiểm tra nếu số cờ còn lại lớn hơn 0 mới cho phép cắm cờ
			if (CTBang.SSoCo < CTBang.SSoBom)
			{
				CTO[SX][SY].BCamCo = true;
				CTBang.SSoCo++;
			}
			else
			{
				// Nếu không còn cờ để cắm, có thể thêm thông báo ở đây nếu muốn
				// Ví dụ: printf("Không còn cờ để cắm!\n");
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
			//xét những vị trí không hợp lệ => tiếp tục lặp
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;

			// xét xem ô có bom hay không, có tăng đếm lên 1
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
			if (SSoBomLanCan) // có bom lận cận
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else // ô rỗng
			{
				// duyệt các ô lân cận và gọi đệ quy
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						//xét những vị trí không hợp lệ => tiếp tục lặp
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;

						// gọi đệ quy
						moO(i, j);
					}
				}
			}
		}
	}
}

void clickTrai(short SX, short SY) // mở ô
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
	xoaMang2ChieuDong(); // giải phóng con trỏ
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0);
}

void thua()
{
	// Hiện bon ẩn và kiểm tra cắm cờ đúng hay sai
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo) // có cắm cờ
			{
				if (CTO[i][j].BCoBom)
					veO(j, i, 15); // cắm cờ đúng
				else
					veO(j, i, 14); // cắm cờ sai
			}
			else // không cắm cờ
			{
				if (CTO[i][j].BCoBom) // có bom => hiện bom
					veO(j, i, 9); // hiện bom ẩn
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong(); // giải phóng con trỏ
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2, 2, 0); // cập nhật lại trạng thái thua
}

/// <summary>
/// ý tưởng xử lý menu
/// số 1: menu chính
/// số 2: menu cấp độ
/// số 3: đang chơi game
/// số 4: trang thua
/// số 5: trang thắng
/// số 6: trang lưu game
/// </summary>
/// <param name="key"></param>

void xuKienPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown) // có nhấn phím
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP: // mũi tên lên
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
			}
			//cout << "mũi tên lên" << endl;
			break;
		case VK_DOWN: // mũi tên xuống
			//cout << "mũi tên xuống" << endl;
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
			}
			break;
		case VK_LEFT: // mũi tên trái
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
			}
			//cout << "mũi tên trái" << endl;
			break;
		case VK_RIGHT: // mũi tên phải
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
			}
			//cout << "mũi tên phải" << endl;
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
				else if (SViTriChon == 1) //trang bảng điểm
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
					ExitProcess(0);
				}
				break;
			case 2:
				if (SViTriChon == 0) // dễ
				{
					STrang = 3; // cập nhật lại là đang chơi game
					deleteRow(4, 20);
					khoiTao(9, 9, 10);
				}
				else if (SViTriChon == 1) //trung bình
				{
					STrang = 3; // xập nhật lại là đang chơi game
					deleteRow(4, 20);
					khoiTao(16, 16, 40);
				}
				else if (SViTriChon == 2) // khó
				{
					STrang = 3; // xập nhật lại là đang chơi game
					deleteRow(4, 20);
					khoiTao(24, 24, 99);
				}
				else
				{
					STrang = 1; // cập nhật lại menu chính
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
			case 6: // trang lưu game
				if (SViTriChon)
				{
					STrang = 1;
					deleteRow(3, ConsoleHieght - 3);
					veMenuChinh(0);
				}
				else
				{
					// lưu game => xử lý file
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
				break;
			case 2:
				STrang = 1; // cập nhật lại trang menu chính
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
				STrang = 1; // cập nhật lại trang menu chính
				deleteRow(4, 20);
				veMenuChinh(0);
				break;
			}
			break;
		case ClickTrai: // phím z - mở ô
			clickTrai(CViTriConTro.Y, CViTriConTro.X);
			//cout << "phím z - mở ô" << endl;
			break;
		case ClickPhai: // phím x - cắm cờ
			//cout << "phím x - cắm cờ" << endl;
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}

void xuLySuKien()
{
	while (1)
	{
		// lưu lại sự kiện hiện tại
		DWORD DWNumberOfEvents = 0;
		// lưu lại số lượng sự kiện đã được lọc
		DWORD DWNumberOfEventsRead = 0;

		// thiết bị ầu vào
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		//đặt sự kiện đầu vào của giao diện cho biến DWNumberOfEvents
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);

		if (DWNumberOfEvents)
		{
			// con trỏ IREventBuffer
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD;
			// đặt các sự kiện được lưu trữ vào con trỏ IREventBuffer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);

			// chạy vòng lặp để đọc sự kiện
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT) // nếu là sự kiện phím
				{
					xuKienPhim(IREventBuffer[i].Event.KeyEvent);
				}
				else if (IREventBuffer[i].EventType == MOUSE_EVENT) // nếu là sự kiện chuột
				{
				}
			}
		}
	}
}

// design
void maximizeConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow(); // Lấy handle của cửa sổ console
	ShowWindow(consoleWindow, SW_MAXIMIZE); // Phóng to cửa sổ console toàn bộ màn hình

	// Thiết lập chế độ buffer để phù hợp với kích thước cửa sổ
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	SMALL_RECT windowSize = { 0, 0, csbi.dwMaximumWindowSize.X - 1, csbi.dwMaximumWindowSize.Y - 1 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

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

	// cập nhật lại vị trí đang chọn và tổng mục của menu
	SViTriChon = Index;
	STongMuc = 2;

	setColorBGTextXY(1, 3, 15, 0, (char*)"Ban Do: %d * %d", CTBang.SDong, CTBang.SCot);
	setColorBGTextXY(1, 4, 15, 0, (char*)"Ban Bom: %d", CTBang.SSoBom - CTBang.SSoCo);

	//vẽ menu thắng thua

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

	//vẽ text trạng thái
	if (STrangThai == 1) // đang chơi game
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, (char*)"Trang Thai: %s", "Dang choi");
	if (STrangThai == 2) // thua
		setColorBGTextXY(ConsoleWidth - 22, 4, 12, 0, (char*)"Trang Thai: %s", "Thua");
	if (STrangThai == 3) // thắng
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
	// cập nhật lại vị trí đang chọn và tổng mục của menu
	SViTriChon = Index;
	STongMuc = 4;

	//vẽ menu
	const char* StrTextMenuChinh1[] = { "  GAME MOI  ", "  BANG DIEM  ", "  THONG TIN  ", "  THOAT  " };

	for (int i = 0; i < STongMuc; ++i)
	{
		char* copy1 = _strdup(StrTextMenuChinh1[i]);
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuChinh1[i]) / 2), 7 + i, 15, (Index == i) ? 5 : 0, copy1);
		// Free the allocated memory after use
		free(copy1);
	}
}

void veMenuCapDo(short Index)
{
	// cập nhật lại vị trí đang chọn và tổng mục của menu
	SViTriChon = Index;
	STongMuc = 4;

	//vẽ menu
	const char* StrTextMenuCapDo[] = { "  DE (9 * 9 VA 10 BOM) ", "  TRUNG BINH (16 * 16 VA 40 BOM)  ", "  KHO (24 * 24 VA 99 BOM)  ", "  TRO VE  " };
	setColorBGTextXY((ConsoleWidth / 2) - 7, 4, 15, 2, (char*)"  CHON CAP DO  ");
	for (int i = 0; i < STongMuc; ++i)
	{
		char* copy2 = _strdup(StrTextMenuCapDo[i]);
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(StrTextMenuCapDo[i]) / 2), 6 + i, 15, (Index == i) ? 5 : 0, copy2);
		// Free the allocated memory after use
		free(copy2);
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