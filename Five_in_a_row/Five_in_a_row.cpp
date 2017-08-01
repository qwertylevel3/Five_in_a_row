// Five_in_a_row.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#pragma comment(lib,"msimg32.lib")

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HBITMAP hBitmapMap;
HBITMAP hBitmapWhite;
HBITMAP hBitmapBlack;

HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
GameEngine g_gGameEngine;						// ��Ϸ����
int currColor=0;								// ��ǰ��ɫ
int g_iDifficult=0;								// �Ѷȵȼ�����Ϸģʽ��
bool g_bGameStart=false;						// ��Ϸ�Ƿ�ʼ
bool g_bPlayerFirst;							// ����Ƿ�����

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FIVE_IN_A_ROW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIVE_IN_A_ROW));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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

		hwndButtonQuit = CreateWindow(TEXT("button"),TEXT("�˳�"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			800,620,100,30,hWnd,(HMENU)IDM_QUIT,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButtonAgain = CreateWindow(TEXT("button"),TEXT("���¿�ʼ"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			800,550,100,30,hWnd,(HMENU)IDM_AGAIN,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButtonAgain = CreateWindow(TEXT("button"),TEXT("����"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			800,480,100,30,hWnd,(HMENU)IDM_REMOVE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		srand(time(NULL));
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
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
				MessageBox(hWnd,TEXT("��Ұ׻�ʤ"),TEXT("��Ϸ����"),0);
				InvalidateRect(hWnd,NULL,FALSE);
				g_gGameEngine.initialize(hInstance);
				legal=false;
			}
			else if(g_gGameEngine.judge()==1)
			{
				MessageBox(hWnd,TEXT("��Һڻ�ʤ"),TEXT("��Ϸ����"),0);
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
					MessageBox(hWnd,TEXT("���Ի�ʤ"),TEXT("��Ϸ����"),0);
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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