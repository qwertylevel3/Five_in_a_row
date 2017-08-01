// Five_in_a_row.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(lib,"msimg32.lib")

#define MAX_LOADSTRING 100

// 全局变量:
HBITMAP hBitmapMap;
HBITMAP hBitmapWhite;
HBITMAP hBitmapBlack;

HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
GameEngine g_gGameEngine;						// 游戏引擎
int currColor=0;								// 当前颜色
int g_iDifficult=0;								// 难度等级（游戏模式）
bool g_bGameStart=false;						// 游戏是否开始
bool g_bPlayerFirst;							// 玩家是否先手

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FIVE_IN_A_ROW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIVE_IN_A_ROW));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIVE_IN_A_ROW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FIVE_IN_A_ROW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle,WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
      150, 10, xClient, yClient, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static HINSTANCE hInstance;
	int x,y;
	static HWND hwndButtonQuit;
	static HWND hwndButtonAgain;

	switch (message)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		hBitmapMap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
		hBitmapBlack = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
		hBitmapWhite = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
		g_gGameEngine.setHwnd(hWnd);
		g_gGameEngine.initialize(hInstance);

		hwndButtonQuit = CreateWindow(TEXT("button"),TEXT("退出"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			800,620,100,30,hWnd,(HMENU)IDM_QUIT,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButtonAgain = CreateWindow(TEXT("button"),TEXT("重新开始"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			800,550,100,30,hWnd,(HMENU)IDM_AGAIN,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButtonAgain = CreateWindow(TEXT("button"),TEXT("悔棋"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			800,480,100,30,hWnd,(HMENU)IDM_REMOVE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		srand(time(NULL));
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_QUIT:
			DestroyWindow(hWnd);
			break;
		case IDM_AGAIN:
			g_gGameEngine.initialize(hInstance);
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_REMOVE:
			g_gGameEngine.remove();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		x=(LOWORD(lParam)-50)/(680/19);
		y=(HIWORD(lParam)-16)/(680/19);
		if(x<19 && LOWORD(lParam)>42 && y<19 && HIWORD(lParam)>16)
		{
			
			Record r;
			r.color = currColor;
			r.position.x=x;
			r.position.y=y;

			bool legal=g_gGameEngine.position_legal(r.position);

			g_gGameEngine.playerMove(r);
			InvalidateRect(hWnd,NULL,FALSE);
			if(g_gGameEngine.judge()==0)
			{
				MessageBox(hWnd,TEXT("玩家白获胜"),TEXT("游戏结束"),0);
				InvalidateRect(hWnd,NULL,FALSE);
				g_gGameEngine.initialize(hInstance);
				legal=false;
			}
			else if(g_gGameEngine.judge()==1)
			{
				MessageBox(hWnd,TEXT("玩家黑获胜"),TEXT("游戏结束"),0);
				InvalidateRect(hWnd,NULL,FALSE);
				g_gGameEngine.initialize(hInstance);
				legal=false;
			}
			if(g_bGameStart && legal)
			{
				switch(g_iDifficult)
				{
				case Easy:
					g_gGameEngine.AIEasy();
					break;
				//case Normal:
				//	g_gGameEngine.AINormal();
				//	break;
				//case Hard:
				//	g_gGameEngine.AIHard();
				//	break;
				case PvP:
				default:
					break;
				}
				InvalidateRect(hWnd,NULL,FALSE);
				if(g_gGameEngine.judge()!=-1)
				{
					MessageBox(hWnd,TEXT("电脑获胜"),TEXT("游戏结束"),0);
					InvalidateRect(hWnd,NULL,FALSE);
					g_gGameEngine.initialize(hInstance);
				}
			}

		}
		else
			MessageBeep(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		g_gGameEngine.paint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmapMap);
		DeleteObject(hBitmapBlack);
		DeleteObject(hBitmapWhite);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
int CALLBACK DlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	HWND hParent = GetParent(hDlg);


	switch(message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_BUTTON1,IDC_BUTTON4,IDC_BUTTON1);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR));
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			g_iDifficult=Easy;
			g_bGameStart=true;
			EndDialog(hDlg, LOWORD(wParam));
			return Easy;
		//case IDC_BUTTON2:
		//	g_iDifficult=Normal;
		//	g_bGameStart=true;
		//	EndDialog(hDlg, LOWORD(wParam));
		//	return Normal;
		//case IDC_BUTTON3:
		//	g_iDifficult=Hard;
		//	g_bGameStart=true;
		//	EndDialog(hDlg, LOWORD(wParam));
		//	return Hard;
		case IDC_BUTTON4:
			g_iDifficult=PvP;
			g_bGameStart=true;
			EndDialog(hDlg,LOWORD(wParam));
			return PvP;
		case IDC_BUTTON5:
			DestroyWindow(hParent);
			EndDialog(hDlg, LOWORD(wParam));
			return 0;
		}
	}
	return 0;
}
BOOL CALLBACK ChooseProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_BUTTON1,IDC_BUTTON4,IDC_BUTTON1);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR));
		return true;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			g_bPlayerFirst=true;
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		case IDC_BUTTON2:
			g_bPlayerFirst=false;
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		}
	}
	return false;
}