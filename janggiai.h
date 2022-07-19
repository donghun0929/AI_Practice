#pragma once
#include "T3Dlg.h"


//extern int move[10][9];

extern int unit_move[10][9];
extern int now_x, now_y, next_x, next_y;
class janggiai
{
	//int map[10][9];
	//int unit_move[10][9] = { 0 };

public:
	//int move[MAX_Y_COUNT][MAX_X_COUNT] = { 0 };
	void movee(int y, int x);
	void ai();
};

