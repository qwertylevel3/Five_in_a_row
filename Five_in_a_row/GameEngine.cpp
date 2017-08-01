#include"stdafx.h"

extern HBITMAP hBitmapMap;
extern HBITMAP hBitmapWhite;
extern HBITMAP hBitmapBlack;

char wFive[5]={'0','0','0','0','0'};
char wLive_four[6]={'/','0','0','0','0','/'};
char wDie_four_a_1[5]={'0','0','0','0','/'};
char wDie_four_a_2[5]={'/','0','0','0','0'};
char wDie_four_b_1[5]={'0','0','0','/','0'};
char wDie_four_b_2[5]={'0','/','0','0','0'};
char wDie_four_c[5]={'0','0','/','0','0'};
//char wLive_three[7]={'/','/','0','0','0','/','/'};
char wLive_three[5]={'/','0','0','0','/'};
char wDie_three_a_1[5]={'0','0','0','/','/'};
char wDie_three_a_2[5]={'/','/','0','0','0'};
char wDie_three_b_1[6]={'/','0','/','0','0','/'};
char wDie_three_b_2[6]={'/','0','0','/','0','/'};
char wDie_three_c_1[5]={'0','/','/','0','0'};
char wDie_three_c_2[5]={'0','0','/','/','0'};
char wDie_three_d[5]={'0','0','/','0','0'};
char wLive_two[8]={'/','/','/','0','0','/','/','/'};
char wDie_two_a_1[5]={'0','0','/','/','/'};
char wDie_two_a_2[5]={'/','/','/','0','0'};
char wDie_two_b[7]={'/','/','0','/','0','/','/'};
char wDie_two_c[6]={'/','0','/','/','0','/'};

char bFive[5]={'1','1','1','1','1'};
char bLive_four[6]={'/','1','1','1','1','/'};
char bDie_four_a_1[5]={'1','1','1','1','/'};
char bDie_four_a_2[5]={'/','1','1','1','1'};
char bDie_four_b_1[5]={'1','1','1','/','1'};
char bDie_four_b_2[5]={'1','/','1','1','1'};
char bDie_four_c[5]={'1','1','/','1','1'};
char bLive_three[5]={'/','1','1','1','/'};
char bDie_three_a_1[5]={'1','1','1','/','/'};
char bDie_three_a_2[5]={'/','/','1','1','1'};
char bDie_three_b_1[6]={'/','1','/','1','1','/'};
char bDie_three_b_2[6]={'/','1','1','/','1','/'};
char bDie_three_c_1[5]={'1','/','/','1','1'};
char bDie_three_c_2[5]={'1','1','/','/','1'};
char bDie_three_d[5]={'1','1','/','1','1'};
char bLive_two[8]={'/','/','/','1','1','/','/','/'};
char bDie_two_a_1[5]={'1','1','/','/','/'};
char bDie_two_a_2[5]={'/','/','/','1','1'};
char bDie_two_b[7]={'/','/','1','/','1','/','/'};
char bDie_two_c[6]={'/','1','/','/','1','/'};


//遍历所有可能的着子点,返回权值最大的位置
//遍历整个棋盘压力太大...
POINT GameEngine::traversal()
{
	//镜像棋盘
	int tempmap[19][19];
	for(int i=0;i<19;++i)
		for(int j=0;j<19;j++)
			tempmap[i][j]=map[i][j];

	int max=-Infinity;
	POINT return_point;
	
	for(int i=trace.get_size()-1;i>=0;i--)
	{
		//对所有已下过的点四周判断（有可能的着子位置）
		POINT p=trace.read(i).position;

		//横向检验
		for(int a=1;a<search_length;a++)
		{
			POINT tp;
			tp.x=p.x+a;
			tp.y=p.y;
			if(tp.x>=0 && tp.x<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		for(int a=-1;a>-search_length;a--)
		{
			POINT tp;
			tp.x=p.x+a;
			tp.y=p.y;
			if(tp.x>=0 && tp.x<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		//纵向检验
		for(int a=1;a<search_length;a++)
		{
			POINT tp;
			tp.x=p.x;
			tp.y=p.y+a;
			if(tp.y>=0 && tp.y<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		for(int a=-1;a>-search_length;a--)
		{
			POINT tp;
			tp.x=p.x;
			tp.y=p.y+a;
			if(tp.y>=0 && tp.y<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		//斜向检验
		for(int a=1;a<search_length;a++)
		{
			POINT tp;
			tp.x=p.x+a;
			tp.y=p.y+a;
			if(tp.x>=0 && tp.x<19 && tp.y>=0 && tp.y<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		for(int a=-1;a>-search_length;a--)
		{
			POINT tp;
			tp.x=p.x+a;
			tp.y=p.y+a;
			if(tp.x>=0 && tp.x<19 && tp.y>=0 && tp.y<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		//另一个斜向检验
		for(int a=1;a<search_length;a++)
		{
			POINT tp;
			tp.x=p.x-a;
			tp.y=p.y+a;
			if(tp.x>=0 && tp.x<19 && tp.y>=0 && tp.y<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
		for(int a=-1;a>-search_length;a--)
		{
			POINT tp;
			tp.x=p.x-a;
			tp.y=p.y+a;
			if(tp.x>=0 && tp.x<19 && tp.y>=0 && tp.y<19 && tempmap[tp.x][tp.y]==-1)
			{
				//计算该点权值
				int value=calculate(tp);
				//要是得到的值为无穷大，直接返回（该点已经最好）
				if(value==Infinity) return tp;
				//权值比当前最大权值大，则保存该点
				if(value>max)
				{
					max=value;
					return_point=tp;
				}
				//另该点无效，免得重复查找
				tempmap[tp.x][tp.y]=3;
			}
		}
	}
	return return_point;
}

//匹配白
int GameEngine::matchW(char* P)
{
	if(KMPmatch(P,wFive)!=-1)
	{
		if(currColor==0)
			return Infinity;
		else
			return Infinity-1;
	}
	else if(KMPmatch(P,wLive_four)!=-1)
	{
		return Live_four;
	}
	else if(KMPmatch(P,wDie_four_a_1)!=-1 || KMPmatch(P,wDie_four_a_2)!=-1)
	{
		return Die_four_a;

	}
	else if(KMPmatch(P,wDie_four_b_1)!=-1 || KMPmatch(P,wDie_four_b_2)!=-1)
	{
		return Die_four_b;
	}
	else if(KMPmatch(P,wDie_four_c)!=-1)
	{
		return Die_four_c;

	}
	else if(KMPmatch(P,wLive_three)!=-1)
	{
		return Live_three;

	}
	else if(KMPmatch(P,wDie_three_a_1)!=-1 || KMPmatch(P,wDie_three_a_2)!=-1)
	{
		return Die_three_a;
	}
	else if(KMPmatch(P,wDie_three_b_1)!=-1 || KMPmatch(P,wDie_three_b_2)!=-1)
	{
		return Die_three_b;

	}
	else if(KMPmatch(P,wDie_three_c_1)!=-1 || KMPmatch(P,wDie_three_c_2)!=-1)
	{
		return Die_three_c;
	}
	else if(KMPmatch(P,wDie_three_d)!=-1)
	{
		return Die_three_d;

	}
	else if(KMPmatch(P,wLive_two)!=-1)
	{
		return Live_two;
	}
	else if(KMPmatch(P,wDie_two_a_1)!=-1 || KMPmatch(P,wDie_two_a_2)!=-1)
	{
		return Die_two_a;

	}
	else if(KMPmatch(P,wDie_two_b)!=-1)
	{
		return Die_two_b;

	}
	else if(KMPmatch(P,wDie_two_c)!=-1)
	{
		return Die_two_c;

	}
	return 0;
	

}

//匹配黑
int GameEngine::matchB(char* P)
{

	if(KMPmatch(P,bFive)!=-1 )
	{
		if(currColor==1)
			return Infinity;
		else
			return Infinity-1;
	}
	else if(KMPmatch(P,bLive_four)!=-1)
	{
		return Live_four;
	}
	else if(KMPmatch(P,bDie_four_a_1)!=-1 || KMPmatch(P,bDie_four_a_2)!=-1)
	{
		return Die_four_a;

	}
	else if(KMPmatch(P,bDie_four_b_1)!=-1 || KMPmatch(P,bDie_four_b_2)!=-1)
	{
		return Die_four_b;
	}
	else if(KMPmatch(P,bDie_four_c)!=-1)
	{
		return Die_four_c;

	}
	else if(KMPmatch(P,bLive_three)!=-1)
	{
		return Live_three;

	}
	else if(KMPmatch(P,bDie_three_a_1)!=-1 || KMPmatch(P,bDie_three_a_2)!=-1)
	{
		return Die_three_a;
	}
	else if(KMPmatch(P,bDie_three_b_1)!=-1 || KMPmatch(P,bDie_three_b_2)!=-1)
	{
		return Die_three_b;

	}
	else if(KMPmatch(P,bDie_three_c_1)!=-1 || KMPmatch(P,bDie_three_c_2)!=-1)
	{
		return Die_three_c;
	}
	else if(KMPmatch(P,bDie_three_d)!=-1)
	{
		return Die_three_d;

	}
	else if(KMPmatch(P,bLive_two)!=-1)
	{
		return Live_two;
	}
	else if(KMPmatch(P,bDie_two_a_1)!=-1 || KMPmatch(P,bDie_two_a_2)!=-1)
	{
		return Die_two_a;

	}
	else if(KMPmatch(P,bDie_two_b)!=-1)
	{
		return Die_two_b;

	}
	else if(KMPmatch(P,bDie_two_c)!=-1)
	{
		return Die_two_c;

	}
	return 0;


}

//p点计算权值大小
int GameEngine::calculate(POINT p)
{
	int value=0;
	POINT tp=p;
	int tcol=currColor;

	char P[9];
	for(int i=0;i<9;i++)
	{
		P[i]='#';
	}
	P[4]=48;
	//当前横向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.x+i>=19) break;
		P[4+i]=map[tp.x+i][tp.y]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.x-i<0) break;
		P[4-i]=map[tp.x-i][tp.y]+48;
	}
	//模式匹配
	if(tp.x==9 && tp.y==8)
		int i=0;
	int tempvalue=matchW(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;





	//当前纵向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.y+i>=19) break;
		P[4+i]=map[tp.x][tp.y+i]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.y-i<0) break;
		P[4-i]=map[tp.x][tp.y-i]+48;
	}
	//模式匹配
	tempvalue=matchW(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;

	//斜向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.y+i>=19) break;
		if(tp.x+i>=19) break;
		P[4+i]=map[tp.x+i][tp.y+i]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.y-i<0) break;
		if(tp.x-i<0) break;
		P[4-i]=map[tp.x-i][tp.y-i]+48;
	}
	tempvalue=matchW(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;


	//斜向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.y-i>=19) break;
		if(tp.x+i>=19) break;
		P[4+i]=map[tp.x+i][tp.y-i]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.y+i<0) break;
		if(tp.x-i<0) break;
		P[4-i]=map[tp.x-i][tp.y+i]+48;
	}
	if(tp.x==12 && tp.y==6 )
		int i=0;
	tempvalue=matchW(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;


	P[4]=48+1;
	//当前横向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.x+i>=19) break;
		P[4+i]=map[tp.x+i][tp.y]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.x-i<0) break;
		P[4-i]=map[tp.x-i][tp.y]+48;
	}
	//模式匹配
	tempvalue=matchB(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;





	//当前纵向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.y+i>=19) break;
		P[4+i]=map[tp.x][tp.y+i]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.y-i<0) break;
		P[4-i]=map[tp.x][tp.y-i]+48;
	}
	//模式匹配
	tempvalue=matchB(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;

	//斜向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.y+i>=19) break;
		if(tp.x+i>=19) break;
		P[4+i]=map[tp.x+i][tp.y+i]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.y-i<0) break;
		if(tp.x-i<0) break;
		P[4-i]=map[tp.x-i][tp.y-i]+48;
	}
	tempvalue=matchB(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;


	//斜向棋型
	for(int i=1;i<search_length;i++)
	{
		if(tp.y-i>=19) break;
		if(tp.x+i>=19) break;
		P[4+i]=map[tp.x+i][tp.y-i]+48;
	}
	for(int i=1;i<search_length;i++)
	{
		if(tp.y+i<0) break;
		if(tp.x-i<0) break;
		P[4-i]=map[tp.x-i][tp.y+i]+48;
	}
	tempvalue=matchB(P);
	if(tempvalue>=Infinity)
		return Infinity;
	else
		value+=tempvalue;

	return value;
}

void GameEngine::AIEasy()
{
	Record r;
	POINT p;

	if(traceNumber==1)//第二步随便走
	{
		int i=trace.read(0).position.x;
		int j=trace.read(0).position.y;
		int tx=0;
		int ty=0;
		int itemp=rand();
		if(itemp%3==0)
			tx=1;
		else if(itemp%3==1)
			tx=-1;
		else
			tx=0;

		itemp=rand();
		if(itemp%3==0)
			ty=1;
		else if(itemp%3==1)
			ty=-1;
		else if(tx==0)
			ty=1;
		else
			ty=0;
		i+=tx;
		j+=ty;


		p.x=i;
		p.y=j;
		r.position=p;
		r.color=currColor;
	
		map[r.position.x][r.position.y]=r.color;
		trace.push(r);
		traceNumber++;
		currColor=1-currColor;
		
	}
	else
	{
		p = traversal();
		r.position=p;
		r.color=currColor;
		if(map[r.position.x][r.position.y]==-1)
		{
			map[r.position.x][r.position.y]=r.color;
			trace.push(r);
			traceNumber++;
			currColor=1-currColor;
		}
	}




}

int GameEngine::judge()
{
	g_bGameStart=false;
	//得到刚刚下的一步的信息
	Record r=trace.read(trace.get_size()-1);
	int col = r.color;

	//判断4个方向有没有到达5子
	int tx=r.position.x;
	int ty=r.position.y;
	int count=0;
	while(map[tx][ty]==col && tx >= 0 && tx < 19)
	{
		--tx;
		++count;
	}
	tx=r.position.x+1;
	ty=r.position.y;
	while(map[tx][ty]==col && tx >= 0 && tx < 19)
	{
		++tx;
		++count;
	}
	if(count>=5)
		return col;

	count=0;
	tx=r.position.x;
	ty=r.position.y;
	while(map[tx][ty]==col && ty>=0 && ty<19)
	{
		--ty;
		++count;
	}
	tx=r.position.x;ty=r.position.y+1;
	while(map[tx][ty]==col && ty>=0 && ty<19)
	{
		++ty;
		++count;
	}
	if(count>=5)
		return col;

	count=0;
	tx=r.position.x;
	ty=r.position.y;
	while(map[tx][ty]==col && ty>=0 && ty<19 && tx>=0 && tx<19)
	{
		--ty;
		--tx;
		++count;
	}
	tx=r.position.x+1;ty=r.position.y+1;
	while(map[tx][ty]==col && ty>=0 && ty<19 && tx>=0 && tx<19)
	{
		++ty;
		++tx;
		++count;
	}
	if(count>=5)
		return col;

	count=0;
	tx=r.position.x;
	ty=r.position.y;
	while(map[tx][ty]==col && ty>=0 && ty<19 && tx>=0 && tx<19)
	{
		++ty;
		--tx;
		++count;
	}
	tx=r.position.x+1;ty=r.position.y-1;
	while(map[tx][ty]==col && ty>=0 && ty<19 && tx>=0 && tx<19)
	{
		--ty;
		++tx;
		++count;
	}
	if(count>=5)
		return col;
	g_bGameStart=true;
	return -1;
}
void GameEngine::initialize(HINSTANCE hInstance)
{
	for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
			map[i][j]=-1;
	int n=trace.get_size();
	for(int i=0;i<n;i++)
		trace.remove(0);
	traceNumber=0;
	currColor=0;
	g_bGameStart=false;
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR),hWnd,DlgProc);
	if(g_iDifficult!=PvP)
	{
		DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR1),hWnd,ChooseProc);
		if(g_bPlayerFirst==false)//要是玩家后手，先在中间走一步
		{
			Record r;
			r.position.x=9;
			r.position.y=9;
			r.color=currColor;
			map[9][9]=r.color;
			trace.push(r);
			traceNumber++;
			currColor=1-currColor;
			InvalidateRect(hWnd,NULL,FALSE);
		}
	}

}
void GameEngine::paint(HDC hdc)
{
	HDC hdcMem;
	hdcMem = CreateCompatibleDC(hdc);	

	SelectObject(hdcMem,hBitmapMap);
	BitBlt(hdc,0,0,1000,750,hdcMem,0,25,SRCCOPY);
	SetBkMode(hdc,TRANSPARENT);
	TCHAR szBuffer[100];
	TextOut(hdc,810,430,szBuffer,wsprintf(szBuffer,TEXT("步数：%i 步"),traceNumber));

	for(int i=0;i<trace.get_size();i++)
	{
		Record r = trace.read(i);
		if(r.color==0)
		{
			SelectObject(hdcMem,hBitmapWhite);
			TransparentBlt(hdc, (r.position.x)*34.5+47, (r.position.y)*34.5+19, 31, 31, hdcMem, 0, 0,
				31, 31, RGB(255,0,255));
		}
		else if(r.color==1)
		{
			SelectObject(hdcMem,hBitmapBlack);
			TransparentBlt(hdc, (r.position.x)*34.5+47, (r.position.y)*34.5+19, 32, 32, hdcMem, 0, 0,
				32, 32, RGB(255,0,255));
		}
	}

	DeleteDC(hdcMem);
}
void GameEngine::playerMove(Record r)
{
	if(map[r.position.x][r.position.y]==-1)
	{
		map[r.position.x][r.position.y]=r.color;
		trace.push(r);
		traceNumber++;
		currColor=1-currColor;
	}

}
bool GameEngine::position_legal(POINT p)
{
	if(map[p.x][p.y]==-1)
		return true;
	else 
		return false;
}
void GameEngine::remove()
{
	if(g_iDifficult!=4)//人机
	{
		if(!trace.empty())
		{
			Record temp=trace.getLast();
			trace.pop();
			map[temp.position.x][temp.position.y]=-1;
			traceNumber--;
		}
		
		if(!trace.empty())
		{
			Record temp=trace.getLast();
			trace.pop();
			map[temp.position.x][temp.position.y]=-1;
			traceNumber--;
		}

	}
	else
	{
		if(!trace.empty())
		{
			Record temp=trace.getLast();
			trace.pop();
			map[temp.position.x][temp.position.y]=-1;
			traceNumber--;
			currColor=1-currColor;
		}

	}

	InvalidateRect(hWnd,NULL,FALSE);//重新绘制
}


