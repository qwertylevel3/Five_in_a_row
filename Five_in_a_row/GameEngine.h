#pragma once

#include"TVector.h"
#include<Windows.h>
#include"Five_in_a_row.h"

extern int currColor;
extern bool g_bGameStart;
extern bool g_bPlayerFirst;
extern int g_iDifficult;
extern int currColor;

int CALLBACK DlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK ChooseProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);

struct Record
{
	POINT position;
	int color;//0白1黑-1空3已经搜索过
	Record(){}
	Record(const Record& r)
	{
		position.x=r.position.x;
		position.y=r.position.y;
		color=r.color;
	}
	Record operator=(const Record tr)
	{
		position.x=tr.position.x;
		position.y=tr.position.y;
		color=tr.color;
		return *this;
	}

};

class GameEngine
{
protected:
	int map[19][19];
	MyVector<Record> trace;
	HWND hWnd;
	int traceNumber;
public:
	GameEngine(){}
	GameEngine(HWND hwnd):hWnd(hwnd){}
	void initialize(HINSTANCE hInstance);
	void paint(HDC hdc);
	void setHwnd(HWND hwnd){ hWnd=hwnd;}
	int judge();
	void AIEasy();
	//void AINormal();
	//void AIHard();
	POINT traversal();
	int matchW(char* P);//匹配白棋型，返回该棋型对应权值
	int matchB(char* P);//匹配黑棋型，返回该棋型对应权值
	int calculate(POINT p);//计算该点权值
	bool position_legal(POINT p);
	void playerMove(Record r);
	void remove();//悔棋

};


