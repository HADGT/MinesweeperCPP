#pragma once
#include <iostream>
#include "resource.h"
#include <Windows.h>

//#pragma comment(lib, "winm.lib")
//#define AmThanh(fileName) PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandleW(NULL), SND_RESOURCE | SND_ASYNC)

#define ConsoleWidth 80
#define ConsoleHieght 45
#define ClickTrai 0x5A
#define ClickPhai 0x58

struct CauTrucBang
{
	short SDong = 0;
	short SCot = 0;
	short SSoBom = 0;
	short SSoODaMo = 0;
	short SSoCo = 0;
};

struct CauTrucO 
{
	bool BCoBom = false;
	bool BDaMo = false;
	bool BCamCo = false;
	short SBomLanCan = 0;
};

//Trang, vị trí đang chọn, tổng mục
extern short STrang, SViTriChon, STongMuc;
