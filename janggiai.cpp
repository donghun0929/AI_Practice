#include "stdafx.h"
#include "janggiai.h"

#include "iostream"
#include <vector>
//#include "T3Dlg.cpp"

//int janggi[MAX_Y_COUNT][MAX_X_COUNT];
using namespace std;
int unit_move[10][9] = { 0 };
int aimap[10][9];
int now_x = 0;
int now_y = 0;
int next_x = 0;
int next_y = 0;
int full = 1;
int constx;
int consty;
int constx2;
int consty2;

int maxai(int(*aimap)[9], int cnt, int a, int b);
int minai(int(*aimap)[9], int cnt, int a, int b);
void moveai(vector <pair <int, int > > &move, int y, int x, int turn);

int valuee(int x, int i) {
	if (i == 1)   // start value
	{

		if (x % 10 == 7) return 2;
		if (x % 10 == 6) return 3;
		if (x % 10 == 5) return 4;
		if (x % 10 == 4) return 5;
		if (x % 10 == 3) return 3;
		if (x % 10 == 2) return 6;
		if (x % 10 == 1) return 5;
		if (x % 10 == 0) return 1;

	}
	else if (i == 0) {        // end value
		//if (x%10==7) return 10000;
		if (x == 17) return 500;
		if (x == 7) return 1000;
		if (x % 10 == 6) return 20;
		if (x % 10 == 5) return 27;
		if (x % 10 == 4) return 24;
		if (x % 10 == 3) return 23;
		if (x % 10 == 2) return 22;
		if (x % 10 == 1) return 21;
		if (x == 0) return 19;
	}
}


int maxai(int(*aimap)[9], int cnt, int a, int b) {
	if (cnt <= 0)
		return 0;
	vector < pair<int, int > > move;
	int value, temp;
	int score = -99999;
	int k = 0;
	int big = -99999;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (aimap[i][j] > 10) {
				moveai(move, i, j, 1); //pc
				int vs = move.size();
				temp = aimap[i][j];
				while (vs--)
				{

					consty = i;
					constx = j;
					consty2 = move[vs].first;
					constx2 = move[vs].second;
					value = aimap[move[vs].first][move[vs].second];

					if (cnt == full && aimap[move[vs].first][move[vs].second] == 7) {
						now_x = j; now_y = i;
						next_x = move[vs].second;  next_y = move[vs].first;
						goto end;
					}

					aimap[move[vs].first][move[vs].second] = temp;
					aimap[i][j] = 0;

					k = minai(aimap, cnt, a, b) + valuee(temp, 1) + valuee(value, 0);

					if (big < k) {
						big = k;
						b = k - (valuee(temp, 1) + valuee(value, 0));
					}
					if (valuee(value, 0) == 1000) {
						aimap[move[vs].first][move[vs].second] = value;
						aimap[i][j] = temp;
						while (vs--)
						{
							move.pop_back();
						}
						goto alpha;
					}
					if (a != -99999 && k - (valuee(temp, 1) + valuee(value, 0)) >= a) {
						aimap[move[vs].first][move[vs].second] = value;
						aimap[i][j] = temp;
						while (vs--)
						{
							move.pop_back();
						}
						goto alpha;
					}

					if (cnt == full && score < k)
					{
						score = k;
						now_x = j; now_y = i;
						next_x = move[vs].second;  next_y = move[vs].first;

					}
					aimap[move[vs].first][move[vs].second] = value;
					aimap[i][j] = temp;
					move.pop_back();
				}

			}
		}
	}
	if (cnt == full) {
		return score;
	end:
		return score;
	}
	return big;
alpha:
	return 99999;

}

int minai(int(*aimap)[9], int cnt, int a, int b) {
	int k = 0;
	int smalll = 99999;
	vector < pair<int, int > > move2;
	int value, temp;

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (aimap[i][j] > 0 && aimap[i][j] < 10) {

				moveai(move2, i, j, 0); //user
				int vs2 = move2.size();
				temp = aimap[i][j];

				while (vs2--)
				{
					value = aimap[move2[vs2].first][move2[vs2].second];
					aimap[i][j] = 0;


					aimap[move2[vs2].first][move2[vs2].second] = temp;
					k = maxai(aimap, cnt - 1, a, b) - (valuee(temp, 1) + valuee(value, 0));
					if (valuee(value, 0) == 500) {
						aimap[move2[vs2].first][move2[vs2].second] = value;
						aimap[i][j] = temp;
						while (vs2--)
						{
							move2.pop_back();
						}
						goto beta;

					}
					if (b != 99999 && k + (valuee(temp, 1) + valuee(value, 0)) <= b) {
						aimap[move2[vs2].first][move2[vs2].second] = value;
						aimap[i][j] = temp;
						while (vs2--)
						{
							move2.pop_back();
						}
						goto beta;
					}

					if (k < smalll) {
						smalll = k;
						a = k + (valuee(temp, 1) + valuee(value, 0));
					}
					aimap[move2[vs2].first][move2[vs2].second] = value;
					aimap[i][j] = temp;
					move2.pop_back();
				}
			}
		}
	}

	return smalll;

beta:
	return -99999;
}



void moveai(vector <pair <int, int > > &move, int y, int x, int turn) {
	int ori_x = x;
	int ori_y = y;
	if ((aimap[ori_y][ori_x] % 10) == 3) { //��
		for (int i = ori_y - 1; i >= 0; --i) //up
		{
			/*gotoxy(170,50);
			std::cout << map[i][ori_x] << "-------\n";*/
			if (aimap[i][ori_x] == 0) {
				move.push_back({ i,ori_x });
			}
			else if (aimap[i][ori_x] > 10) {
				if (turn == 0)
					move.push_back({ i,ori_x });
				break;
			}
			else if (aimap[i][ori_x] > 0 && aimap[i][ori_x] < 10) {
				if (turn == 1)
					move.push_back({ i,ori_x });
				break;
			}
		}
		for (int i = ori_y + 1; i < 10; ++i) //down
		{
			if (aimap[i][ori_x] == 0) {
				move.push_back({ i,ori_x });
			}
			else if (aimap[i][ori_x] > 10) {
				if (turn == 0)
					move.push_back({ i,ori_x });
				break;
			}
			else if (aimap[i][ori_x] > 0 && aimap[i][ori_x] < 10) {
				if (turn == 1)
					move.push_back({ i,ori_x });
				break;
			}
		}
		for (int i = ori_x - 1; i >= 0; i--) //left
		{
			if (aimap[y][i] == 0)
				move.push_back({ y,i });
			else if (aimap[y][i] > 10) {
				if (turn == 0)
					move.push_back({ y,i });
				break;
			}
			else if (aimap[y][i] > 0 && aimap[y][i] < 10) {
				if (turn == 1)
					move.push_back({ y,i });
				break;
			}
		}
		for (int i = ori_x + 1; i < 9; i++) //right
		{

			if (aimap[y][i] == 0)
				move.push_back({ y,i });
			else if (aimap[y][i] > 10) {
				if (turn == 0)
					move.push_back({ y,i });
				break;
			}
			else if (aimap[y][i] > 0 && aimap[y][i] < 10) {
				if (turn == 1)
					move.push_back({ y,i });
				break;
			}
		}

	}
	if ((aimap[ori_y][ori_x] % 10) == 2) {//��
		if (x - 2 >= 0 && y - 3 >= 0) {    //up-left
			if (aimap[y - 1][x] == 0 && aimap[y - 2][x - 1] == 0)
			{
				if ((turn == 0) && (aimap[y - 3][x - 2] == 0 || aimap[y - 3][x - 2] > 10))
					move.push_back({ y - 3,x - 2 });
				else if ((turn == 1) && (aimap[y - 3][x - 2] == 0 || aimap[y - 3][x - 2] < 10))
					move.push_back({ y - 3,x - 2 });
			}
		}

		if (y - 3 >= 0 && x + 2 < 9) {    //up-right
			if (aimap[y - 1][x] == 0 && aimap[y - 2][x + 1] == 0)
			{
				if ((turn == 0) && (aimap[y - 3][x + 2] == 0 || aimap[y - 3][x + 2] > 10))
					move.push_back({ y - 3,x + 2 });
				else if ((turn == 1) && (aimap[y - 3][x + 2] == 0 || aimap[y - 3][x + 2] < 10))
					move.push_back({ y - 3,x + 2 });
			}
		}

		if (x + 3 < 9 && y - 2 >= 0) {    //right-up
			if (aimap[y][x + 1] == 0 && aimap[y - 1][x + 2] == 0)
			{
				if ((turn == 0) && (aimap[y - 2][x + 3] == 0 || aimap[y - 2][x + 3] > 10))
					move.push_back({ y - 2,x + 3 });
				else if ((turn == 1) && (aimap[y - 2][x + 3] == 0 || aimap[y - 2][x + 3] < 10))
					move.push_back({ y - 2,x + 3 });
			}
		}

		if (x + 3 < 9 && y + 2 < 10) {    //right-down
			if (aimap[y][x + 1] == 0 && aimap[y + 1][x + 2] == 0)
			{
				if ((turn == 0) && (aimap[y + 2][x + 3] == 0 || aimap[y + 2][x + 3] > 10))
					move.push_back({ y + 2,x + 3 });
				else if ((turn == 1) && (aimap[y + 2][x + 3] == 0 || aimap[y + 2][x + 3] < 10))
					move.push_back({ y + 2,x + 3 });
			}
		}

		if (x + 2 < 9 && y + 3 < 10) {    //down-rigth
			if (aimap[y + 1][x] == 0 && aimap[y + 2][x + 1] == 0)
			{
				if ((turn == 0) && (aimap[y + 3][x + 2] == 0 || aimap[y + 3][x + 2] > 10))
					move.push_back({ y + 3,x + 2 });
				else if ((turn == 1) && (aimap[y + 3][x + 2] == 0 || aimap[y + 3][x + 2] < 10))
					move.push_back({ y + 3,x + 2 });
			}
		}

		if (x - 2 >= 0 && y + 3 < 10) {    //down-left
			if (aimap[y + 1][x] == 0 && aimap[y + 2][x - 1] == 0)
			{
				if ((turn == 0) && (aimap[y + 3][x - 2] == 0 || aimap[y + 3][x - 2] > 10))
					move.push_back({ y + 3,x - 2 });
				else if ((turn == 1) && (aimap[y + 3][x - 2] == 0 || aimap[y + 3][x - 2] < 10))
					move.push_back({ y + 3,x - 2 });
			}
		}

		if (x - 3 >= 0 && y + 2 < 10) {    //Left-down
			if (aimap[y][x - 1] == 0 && aimap[y + 1][x - 2] == 0)
			{
				if ((turn == 0) && (aimap[y + 2][x - 3] == 0 || aimap[y + 2][x - 3] > 10))
					move.push_back({ y + 2,x - 3 });
				else if ((turn == 1) && (aimap[y + 2][x - 3] == 0 || aimap[y + 2][x - 3] < 10))
					move.push_back({ y + 2,x - 3 });
			}
		}

		if (x - 3 >= 0 && y - 2 >= 0) {    //Left-up
			if (aimap[y][x - 1] == 0 && aimap[y - 1][x - 2] == 0)
			{
				if ((turn == 0) && (aimap[y - 2][x - 3] == 0 || aimap[y - 2][x - 3] > 10))
					move.push_back({ y - 2,x - 3 });
				else if ((turn == 1) && (aimap[y - 2][x - 3] == 0 || aimap[y - 2][x - 3] < 10))
					move.push_back({ y - 2,x - 3 });
			}
		}
	}

	if ((aimap[ori_y][ori_x] % 10) == 1) {//��
		if (x - 1 >= 0 && y - 2 >= 0) {    //up-left
			if (aimap[y - 1][x] == 0)
			{
				if ((turn == 0) && (aimap[y - 2][x - 1] == 0 || aimap[y - 2][x - 1] > 10))
					move.push_back({ y - 2,x - 1 });
				else if ((turn == 1) && (aimap[y - 2][x - 1] == 0 || aimap[y - 2][x - 1] < 10))
					move.push_back({ y - 2,x - 1 });
			}
		}

		if (y - 2 >= 0 && x + 1 < 9) {    //up-right
			if (aimap[y - 1][x] == 0)
			{
				if ((turn == 0) && (aimap[y - 2][x + 1] == 0 || aimap[y - 2][x + 1] > 10))
					move.push_back({ y - 2,x + 1 });
				else if ((turn == 1) && (aimap[y - 2][x + 1] == 0 || aimap[y - 2][x + 1] < 10))
					move.push_back({ y - 2,x + 1 });
			}
		}

		if (x + 2 < 9 && y - 1 >= 0) {    //right-up
			if (aimap[y][x + 1] == 0)
			{
				if ((turn == 0) && (aimap[y - 1][x + 2] == 0 || aimap[y - 1][x + 2] > 10))
					move.push_back({ y - 1,x + 2 });
				else if ((turn == 1) && (aimap[y - 1][x + 2] == 0 || aimap[y - 1][x + 2] < 10))
					move.push_back({ y - 1,x + 2 });
			}
		}

		if (x + 2 < 9 && y + 1 < 10) {    //right-down
			if (aimap[y][x + 1] == 0)
			{
				if ((turn == 0) && (aimap[y + 1][x + 2] == 0 || aimap[y + 1][x + 2] > 10))
					move.push_back({ y + 1,x + 2 });
				else if ((turn == 1) && (aimap[y + 1][x + 2] == 0 || aimap[y + 1][x + 2] < 10))
					move.push_back({ y + 1,x + 2 });
			}
		}

		if (x + 1 < 9 && y + 2 < 10) {    //down-rigth
			if (aimap[y + 1][x] == 0)
			{
				if ((turn == 0) && (aimap[y + 2][x + 1] == 0 || aimap[y + 2][x + 1] > 10))
					move.push_back({ y + 2,x + 1 });
				else if ((turn == 1) && (aimap[y + 2][x + 1] == 0 || aimap[y + 2][x + 1] < 10))
					move.push_back({ y + 2,x + 1 });
			}
		}

		if (x - 1 >= 0 && y + 2 < 10) {    //down-left
			if (aimap[y + 1][x] == 0)
			{
				if ((turn == 0) && (aimap[y + 2][x - 1] == 0 || aimap[y + 2][x - 1] > 10))
					move.push_back({ y + 2,x - 1 });
				else if ((turn == 1) && (aimap[y + 2][x - 1] == 0 || aimap[y + 2][x - 1] < 10))
					move.push_back({ y + 2,x - 1 });
			}
		}

		if (x - 2 >= 0 && y + 1 < 10) {    //Left-down
			if (aimap[y][x - 1] == 0)
			{
				if ((turn == 0) && (aimap[y + 1][x - 2] == 0 || aimap[y + 1][x - 2] > 10))
					move.push_back({ y + 1,x - 2 });
				else if ((turn == 1) && (aimap[y + 1][x - 2] == 0 || aimap[y + 1][x - 2] < 10))
					move.push_back({ y + 1,x - 2 });
			}
		}

		if (x - 2 >= 0 && y - 1 >= 0) {    //Left-up
			if (aimap[y][x - 1] == 0)
			{
				if ((turn == 0) && (aimap[y - 1][x - 2] == 0 || aimap[y - 1][x - 2] > 10))
					move.push_back({ y - 1,x - 2 });
				else if ((turn == 1) && (aimap[y - 1][x - 2] == 0 || aimap[y - 1][x - 2] < 10))
					move.push_back({ y - 1,x - 2 });
			}
		}
	}

	if ((aimap[ori_y][ori_x] % 10) == 5) { //��
		for (int i = ori_y - 1; i >= 0; --i) //up
		{

			if (aimap[i][ori_x] != 0) {
				if (!((aimap[i][ori_x] % 10) == 5)) {
					for (int j = i - 1; j >= 0; --j)
					{
						if (aimap[j][x] != 0)
						{
							if (((aimap[j][ori_x] % 10) == 5)) {

								i = -1;
								break;
							}
							else if (aimap[j][x] > 10 && turn == 0) {
								move.push_back({ j,x });
								i = -1;
								break;
							}
							else if (aimap[j][x] < 10 && turn == 1) {
								move.push_back({ j,x });
								i = -1;
								break;
							}
							i = -1;
							break;
						}
						move.push_back({ j,x });
					}
				}
				i = -1;
				break;
			}
		}
		for (int i = ori_y + 1; i < 10; ++i) //down
		{
			if (aimap[i][ori_x] != 0) {
				if (!((aimap[i][ori_x] % 10) == 5)) {
					for (int j = i + 1; j < 10; ++j)
					{
						if (aimap[j][x] != 0)
						{
							if (((aimap[j][ori_x] % 10) == 5)) {

								i = 10;
								break;
							}
							else if (aimap[j][x] > 10 && turn == 0) {
								move.push_back({ j,x });
								i = 10;
								break;
							}
							else if (aimap[j][x] < 10 && turn == 1) {
								move.push_back({ j,x });
								i = 10;
								break;
							}
							i = 10;
							break;
						}
						move.push_back({ j,x });
					}
				}
				i = 10;
				break;
			}
		}
		for (int i = ori_x - 1; i >= 0; --i) //left
		{
			if (aimap[y][i] != 0) {
				if (!((aimap[y][i] % 10) == 5)) {
					for (int j = i - 1; j >= 0; --j)
					{
						if (aimap[y][j] != 0)
						{
							if (((aimap[y][j] % 10) == 5)) {

								i = -1;
								break;
							}
							else if (aimap[y][j] > 10 && turn == 0) {
								move.push_back({ y,j });
								i = -1;
								break;
							}
							else if (aimap[y][j] < 10 && turn == 1) {
								move.push_back({ y,j });
								i = -1;
								break;
							}
							i = -1;
							break;
						}
						move.push_back({ y,j });
					}
				}
				i = -1;
				break;
			}
		}
		for (int i = ori_x + 1; i < 9; ++i) //right
		{
			if (aimap[y][i] != 0) {
				if (!((aimap[y][i] % 10) == 5)) {
					for (int j = i + 1; j < 9; ++j)
					{
						if (aimap[y][j] != 0)
						{
							if (((aimap[y][j] % 10) == 5)) {

								i = 9;
								break;
							}
							else if (aimap[y][j] > 10 && turn == 0) {
								move.push_back({ y,j });
								i = 9;
								break;
							}
							else if (aimap[y][j] < 10 && turn == 1) {
								move.push_back({ y,j });
								i = 9;
								break;
							}
							i = 9;
							break;
						}
						move.push_back({ y,j });
					}
				}
				i = 9;
				break;
			}
		}


	}

	if ((aimap[ori_y][ori_x] % 10) == 6) {
		if (turn == 0) //user
		{

			if (aimap[y - 1][x] == 0 || aimap[y - 1][x] > 10)
				move.push_back({ y - 1,x });
			if ((aimap[y][x + 1] == 0 || aimap[y][x + 1] > 10) && x + 1 < 9)
				move.push_back({ y,x + 1 });
			if ((aimap[y][x - 1] == 0 || aimap[y][x - 1] > 10) && x - 1 >= 0)
				move.push_back({ y,x - 1 });

		}
		if (turn == 1) //aisddsd
		{

			if (aimap[y + 1][x] == 0 || aimap[y + 1][x] < 10)
				move.push_back({ y + 1,x });
			if ((aimap[y][x + 1] == 0 || aimap[y][x + 1] < 10) && x + 1 < 9)
				move.push_back({ y,x + 1 });
			if ((aimap[y][x - 1] == 0 || aimap[y][x - 1] < 10) && x - 1 >= 0)
				move.push_back({ y,x - 1 });

		}
	}

	if (((aimap[ori_y][ori_x] % 10) == 7) || ((aimap[ori_y][ori_x] % 10) == 4)) {//��,��
		if (turn == 1) {
			if (aimap[y][x - 1] < 10 && x - 1 >= 3)//left
				move.push_back({ y,x - 1 });
			if (aimap[y][x + 1] < 10 && x + 1 < 6)//rigth
				move.push_back({ y,x + 1 });
			if (aimap[y - 1][x] < 10 && y - 1 >= 0)//up
				move.push_back({ y - 1,x });
			if (aimap[y + 1][x] < 10 && y + 1 < 3)//down
				move.push_back({ y + 1,x });
			if ((x == 4 && y == 1) || (x == 5 && y == 2)) {//�밢 �»���
				if (aimap[y - 1][x - 1] < 10)
					move.push_back({ y - 1,x - 1 });
			}
			if ((x == 4 && y == 1) || (x == 3 && y == 2)) {//�밢 ������
				if (aimap[y - 1][x + 1] < 10)
					move.push_back({ y - 1,x + 1 });
			}
			if ((x == 4 && y == 1) || (x == 3 && y == 0)) {//�밢 ������
				if (aimap[y + 1][x + 1] < 10)
					move.push_back({ y + 1,x + 1 });
			}
			if ((x == 4 && y == 1) || (x == 5 && y == 0)) {//�밢 ������
				if (aimap[y + 1][x - 1] < 10)
					move.push_back({ y + 1,x - 1 });
			}

		}
		if (turn == 0)
		{
			if ((aimap[y][x - 1] > 10 || aimap[y][x - 1] == 0) && (x >= 4))//left
				move.push_back({ y,x - 1 });
			if ((aimap[y][x + 1] > 10 || aimap[y][x + 1] == 0) && (x + 1 < 6))//rigth
				move.push_back({ y,x + 1 });
			if ((aimap[y - 1][x] > 10 || aimap[y - 1][x] == 0) && (y - 1 >= 7))//up
				move.push_back({ y - 1,x });
			if ((aimap[y + 1][x] > 10 || aimap[y + 1][x] == 0) && (y + 1 < 10))//down
				move.push_back({ y + 1,x });
			if ((x == 4 && y == 8) || (x == 5 && y == 9)) {//�밢 �»���
				if ((aimap[y - 1][x - 1] > 10 || aimap[y - 1][x - 1] == 0))
					move.push_back({ y - 1,x - 1 });
			}
			if ((x == 4 && y == 8) || (x == 3 && y == 9)) {//�밢 ������
				if ((aimap[y - 1][x + 1] > 10 || aimap[y - 1][x + 1] == 0))
					move.push_back({ y - 1,x + 1 });
			}
			if ((x == 4 && y == 8) || (x == 3 && y == 7)) {//�밢 ������
				if ((aimap[y + 1][x + 1] > 10 || aimap[y + 1][x + 1] == 0))
					move.push_back({ y + 1,x + 1 });
			}
			if ((x == 4 && y == 8) || (x == 5 && y == 7)) {//�밢 ������
				if ((aimap[y + 1][x - 1] > 10 || aimap[y + 1][x - 1] == 0))
					move.push_back({ y + 1,x - 1 });
			}  //move y�� �����Ұ�
		}
	}

}

void janggiai::ai() {
	now_x = 0;
	now_y = 0;

	int z = 0;

	int a = 2;
	full = a;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			aimap[i][j] = janggi[i][j];
	}


	}
	z = maxai(aimap, a, -99999, 99999);
}

void janggiai::movee(int y, int x) {
	//int move[10][9];
	int map[10][9] = { 0 };
	//CT3Dlg a;
	for (size_t i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++) {
			unit_move[i][j] = 0;
			map[i][j] = janggi[i][j];
			
		}
	}


	int ori_x = x;
	int ori_y = y;

	if (map[ori_y][ori_x] < 10)
	{
		if ((map[ori_y][ori_x] % 10) == 3) { //��
			for (int i = ori_y - 1; i >= 0; --i) //up
			{

				if (map[i][ori_x] == 0) {
					unit_move[i][ori_x] = 1;
				}
				else if (map[i][ori_x] > 0 && map[i][ori_x] < 10)
					break;
				else if (map[i][ori_x] > 10) {
					unit_move[i][ori_x] = 1;
					break;
				}

			}
			for (int i = ori_y + 1; i < 10; ++i) //down
			{
				if (map[i][ori_x] == 0)
					unit_move[i][ori_x] = 1;
				else if (map[i][ori_x] > 0 && map[i][ori_x] < 10) {
					break;
				}
				else if (map[i][ori_x] > 10) {
					unit_move[i][ori_x] = 1;
					break;
				}

			}
			for (int i = ori_x - 1; i >= 0; --i) //left
			{
				if (map[y][i] == 0)
					unit_move[y][i] = 1;
				else if (map[y][i]>0&&map[y][i] < 10) {
					break;
				}
				else if (map[y][i] > 10) {
					unit_move[y][i] = 1;
					break;
				}

			}
			for (int i = ori_x + 1; i < 9; ++i) //right
			{

				if (map[y][i] == 0)
					unit_move[y][i] = 1;
				else if (map[y][i]> 0 && map[y][i] < 10)
					break;
				else if (map[y][i] > 10) {

					unit_move[y][i] = 1;
					break;
				}

			}

		}
		if ((map[ori_y][ori_x] % 10) == 2) {//��
			if (x - 2 >= 0 && y - 3 >= 0) {    //up-left
				if (map[y - 1][x] == 0 && map[y - 2][x - 1] == 0)
				{
					if ((map[y - 3][x - 2] == 0 || map[y - 3][x - 2] > 10))
						unit_move[y - 3][x - 2] = 1;
				}
			}

			if (y - 3 >= 0 && x + 2 < 9) {    //up-right
				if (map[y - 1][x] == 0 && map[y - 2][x + 1] == 0)
				{
					if ((map[y - 3][x + 2] == 0 || map[y - 3][x + 2] > 10))
						unit_move[y - 3][x + 2] = 1;
				}
			}

			if (x + 3 < 9 && y - 2 >= 0) {    //right-up
				if (map[y][x + 1] == 0 && map[y - 1][x + 2] == 0)
				{
					if ((map[y - 2][x + 3] == 0 || map[y - 2][x + 3] > 10))
						unit_move[y - 2][x + 3] = 1;

				}
			}

			if (x + 3 < 9 && y + 2 < 10) {    //right-down
				if (map[y][x + 1] == 0 && map[y + 1][x + 2] == 0)
				{
					if ((map[y + 2][x + 3] == 0 || map[y + 2][x + 3] > 10))
						unit_move[y + 2][x + 3] = 1;

				}
			}

			if (x + 2 < 9 && y + 3 < 10) {    //down-rigth
				if (map[y + 1][x] == 0 && map[y + 2][x + 1] == 0)
				{
					if ((map[y + 3][x + 2] == 0 || map[y + 3][x + 2] > 10))
						unit_move[y + 3][x + 2] = 1;
				}
			}

			if (x - 2 >= 0 && y + 3 < 10) {    //down-left
				if (map[y + 1][x] == 0 && map[y + 2][x - 1] == 0)
				{
					if ((map[y + 3][x - 2] == 0 || map[y + 3][x - 2] > 10))
						unit_move[y + 3][x - 2] = 1;
				}
			}

			if (x - 3 >= 0 && y + 2 < 10) {    //Left-down
				if (map[y][x - 1] == 0 && map[y + 1][x - 2] == 0)
				{
					if ((map[y + 2][x - 3] == 0 || map[y + 2][x - 3] > 10))
						unit_move[y + 2][x - 3] = 1;
				}
			}

			if (x - 3 >= 0 && y - 2 >= 0) {    //Left-up
				if (map[y][x - 1] == 0 && map[y - 1][x - 2] == 0)
				{
					if ((map[y - 2][x - 3] == 0 || map[y - 2][x - 3] > 10))
						unit_move[y - 2][x - 3] = 1;
				}
			}
		}

		if ((map[ori_y][ori_x] % 10) == 1) {//��
			if (x - 1 >= 0 && y - 2 >= 0) {    //up-left
				if (map[y - 1][x] == 0)
				{
					if ((map[y - 2][x - 1] == 0 || map[y - 2][x - 1] > 10))
						unit_move[y - 2][x - 1] = 1;
				}
			}

			if (y - 2 >= 0 && x + 1 < 9) {    //up-right
				if (map[y - 1][x] == 0)
				{
					if ((map[y - 2][x + 1] == 0 || map[y - 2][x + 1] > 10))
						unit_move[y - 2][x + 1] = 1;
				}
			}

			if (x + 2 < 9 && y - 1 >= 0) {    //right-up
				if (map[y][x + 1] == 0)
				{
					if ((map[y - 1][x + 2] == 0 || map[y - 1][x + 2] > 10))
						unit_move[y - 1][x + 2] = 1;
				}
			}

			if (x + 2 < 9 && y + 1 < 10) {    //right-down
				if (map[y][x + 1] == 0)
				{
					if ((map[y + 1][x + 2] == 0 || map[y + 1][x + 2] > 10))
						unit_move[y + 1][x + 2] = 1;
				}
			}

			if (x + 1 < 9 && y + 2 < 10) {    //down-rigth
				if (map[y + 1][x] == 0)
				{
					if ((map[y + 2][x + 1] == 0 || map[y + 2][x + 1] > 10))
						unit_move[y + 2][x + 1] = 1;
				}
			}

			if (x - 1 >= 0 && y + 2 < 10) {    //down-left
				if (map[y + 1][x] == 0)
				{
					if ((map[y + 2][x - 1] == 0 || map[y + 2][x - 1] > 10))
						unit_move[y + 2][x - 1] = 1;
				}
			}

			if (x - 2 >= 0 && y + 1 < 10) {    //Left-down
				if (map[y][x - 1] == 0)
				{
					if ((map[y + 1][x - 2] == 0 || map[y + 1][x - 2] > 10))
						unit_move[y + 1][x - 2] = 1;
				}
			}

			if (x - 2 >= 0 && y - 1 >= 0) {    //Left-up
				if (map[y][x - 1] == 0)
				{
					if ((map[y - 1][x - 2] == 0 || map[y - 1][x - 2] > 10))
						unit_move[y - 1][x - 2] = 1;
				}
			}
		}

		if ((map[ori_y][ori_x] % 10) == 5) { //��
			for (int i = ori_y - 1; i >= 0; --i) //up
			{

				if (map[i][ori_x] != 0) {
					if (!((map[i][ori_x] % 10) == 5)) {
						for (int j = i - 1; j >= 0; --j)
						{
							if (map[j][x] != 0)
							{
								if (((map[j][ori_x] % 10) == 5)) {

									i = -1;
									break;
								}
								else if (map[j][x] > 10) {
									unit_move[j][x] = 1;
									i = -1;
									break;
								}
								i = -1;
								break;
							}
							unit_move[j][x] = 1;
						}
					}
					i = -1;
					break;
				}
			}
			for (int i = ori_y + 1; i < 10; ++i) //down
			{
				if (map[i][ori_x] != 0) {
					if (!((map[i][ori_x] % 10) == 5)) {
						for (int j = i + 1; j < 10; ++j)
						{
							if (map[j][x] != 0)
							{
								if (((map[j][ori_x] % 10) == 5)) {

									i = 10;
									break;
								}
								else if (map[j][x] > 10) {
									unit_move[j][x] = 1;
									i = 10;
									break;
								}
								i = 10;
								break;
							}
							unit_move[j][x] = 1;
						}
					}
					i = 10;
					break;
				}
			}
			for (int i = ori_x - 1; i >= 0; --i) //left
			{
				if (map[y][i] != 0) {
					if (!((map[y][i] % 10) == 5)) {
						for (int j = i - 1; j >= 0; --j)
						{
							if (map[y][j] != 0)
							{
								if (((map[y][j] % 10) == 5)) {

									i = -1;
									break;
								}
								else if (map[y][j] > 10) {
									unit_move[y][j] = 1;
									i = -1;
									break;
								}
								i = -1;
								break;
							}
							unit_move[y][j] = 1;
						}
					}
					i = -1;
					break;
				}
			}
			for (int i = ori_x + 1; i < 9; ++i) //right
			{
				if (map[y][i] != 0) {
					if (!((map[y][i] % 10) == 5)) {
						for (int j = i + 1; j < 9; ++j)
						{
							if (map[y][j] != 0)
							{
								if (((map[y][j] % 10) == 5)) {

									i = 9;
									break;
								}
								else if (map[y][j] > 10) {
									unit_move[y][j] = 1;
									i = 9;
									break;
								}
								i = 9;
								break;
							}
							unit_move[y][j] = 1;
						}
					}
					i = 9;
					break;
				}
			}


		}

		if ((map[ori_y][ori_x] % 10) == 6) {
			if (map[y - 1][x] == 0 || map[y - 1][x] > 10)
				unit_move[y - 1][x] = 1;
			if ((map[y][x + 1] == 0 || map[y][x + 1] > 10) && x + 1 < 9)
				unit_move[y][x + 1] = 1;
			if ((map[y][x - 1] == 0 || map[y][x - 1] > 10) && x - 1 >= 0)
				unit_move[y][x - 1] = 1;
		}

		if (((map[ori_y][ori_x] % 10) == 7) || ((map[ori_y][ori_x] % 10) == 4)) {//��,��
			if ((map[y][x - 1] > 10 || map[y][x - 1] == 0) && (x - 1 >= 3))//left
				unit_move[y][x - 1] = 1;
			if ((map[y][x + 1] > 10 || map[y][x + 1] == 0) && (x + 1 < 6))//rigth
				unit_move[y][x + 1] = 1;
			if ((map[y - 1][x] > 10 || map[y - 1][x] == 0) && (y - 1 >= 7))//up
				unit_move[y - 1][x] = 1;
			if ((map[y + 1][x] > 10 || map[y + 1][x] == 0) && (y + 1 < 10))//down
				unit_move[y + 1][x] = 1;
			if ((x == 4 && y == 8) || (x == 5 && y == 9)) {//�밢 �»���
				if ((map[y - 1][x - 1] > 10 || map[y - 1][x - 1] == 0))
					unit_move[y - 1][x - 1] = 1;
			}
			if ((x == 4 && y == 8) || (x == 3 && y == 9)) {//�밢 ������
				if ((map[y - 1][x + 1] > 10 || map[y - 1][x + 1] == 0))
					unit_move[y - 1][x + 1] = 1;
			}
			if ((x == 4 && y == 8) || (x == 3 && y == 7)) {//�밢 ������
				if ((map[y + 1][x + 1] > 10 || map[y + 1][x + 1] == 0))
					unit_move[y + 1][x + 1] = 1;
			}
			if ((x == 4 && y == 8) || (x == 5 && y == 7)) {
				if ((map[y + 1][x - 1] > 10 || map[y + 1][x - 1] == 0))
					unit_move[y + 1][x - 1] = 1;
			}
		}
	}

}

