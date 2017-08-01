#pragma once

#include "resource.h"



//屏幕宽高
#define xClient 1000
#define yClient 750

//难度
#define Easy 1
#define Normal 2
#define Hard 3
#define PvP 4

//无穷大
#define Infinity 999999

//棋型
#define Five 999999//ooooo
#define Live_four 99999//?oooo?
#define Die_four_a 340//oooo?
#define Die_four_b 260//ooo?o
#define Die_four_c 260//oo?oo
#define Live_three 340//?ooo?
#define Die_three_a 80//ooo??
#define Die_three_b 70//?o?oo?
#define Die_three_c 60//o??oo
#define Die_three_d 55//o?o?o
#define Live_two 65//???oo???
#define Die_two_a 15//oo???
#define Die_two_b 50//??o?o??
#define Die_two_c 12//?o??o?

//搜索范围
#define search_length 5
//
#define IDM_QUIT 100
#define IDM_AGAIN 101
#define IDM_REMOVE 102