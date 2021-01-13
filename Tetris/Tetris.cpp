#include <iostream>
#include "Console.h"
#include <string>
#include <conio.h>
#include <ctime>
#include "MinoRotation.h"

const int WEIGHT = 12;
const int HEIGHT = 25;
const int NUM_MINO = 7;
const int LEFT = 75;
const int UP = 72;
const int RIGHT = 77;
const int DOWN = 80;
const int SPACE = 32;
const int QUIT = 81;
const int quit = 113;
const int RETRY = 82;
const int retry = 114;


using namespace std;

// 배경필드
vector<vector<string>> field(HEIGHT, vector<string>(WEIGHT, ""));


// 현재 내려오는 블럭 각도
int degree;

// 현재의 블럭기준점 위치
int pos_x;
int pos_y;

// 스코어
int score = 0;



// 필드 초기화
void field_init()
{
	for (int i = 0; i < HEIGHT - 1; i++)
		for (int j = 1; j < WEIGHT; j++)
			field[i][j] = "  ";
	for (int i = 0;i < HEIGHT ; i++)
	{
		field[i][0] = "■";
		field[i][WEIGHT - 1] = "■";
	}

	for (int i = 0; i < WEIGHT; i++)
	{
		field[HEIGHT - 1][i] = "■";
	}

	field[4][0] = "▣";
	field[4][WEIGHT - 1] = "▣";

	for (int i = 0;i < HEIGHT;i++)
	{
		gotoxy(3, i + 3);
		for (int j = 0;j < WEIGHT;j++)
			cout << field[i][j];
	}
}

void complete_check()
{
	for (int i = 5;i < HEIGHT - 1;i++)
	{
		bool comp_flag = true;
		for (int j = 1;j < WEIGHT - 1;j++)
			if (field[i][j] == "  ")
			{
				comp_flag = false;
				break;
			}

		if (comp_flag)
		{
			score++;
			for (int j = 1;j < WEIGHT - 1; j++)
				for (int k = i; k >= 5;k--)
					field[k][j] = field[k - 1][j];
		}
	}
}

// 왼쪽 빈곳인지 판단
bool move_left(int nowMino)
{
	for (int i = 0;i <= 3;i++)
		for (int j = 0; j <= 3;j++)
			if (mino[nowMino][degree][i][j] == 1)
			{
				if (field[pos_y + i][pos_x + j - 1] != "  ")
					return false;
				break;
			}
	return true;
}

// 오른쪽 빈곳인지 판단
bool move_right(int nowMino)
{
	for (int i = 0;i <= 3;i++)
		for (int j = 3; j >= 0;j--)
			if (mino[nowMino][degree][i][j] == 1)
			{
				if (field[pos_y + i][pos_x + j + 1] != "  ")
					return false;
				break;
			}
	return true;
}

// 아래 빈곳인지 판단
bool move_down(int nowMino)
{
	for (int i = 0; i <= 3; i++)
		for (int j = 3;j >= 0;j--)
			if (mino[nowMino][degree][j][i] == 1)
			{
				if (field[pos_y + j + 1][pos_x + i] != "  ")
					return false;
				break;
			}
	return true;
}

// 게임오버
bool gameover()
{
	for (int i = 1; i < WEIGHT - 2; i++)
		if (field[4][i] != "  ")
		{
			Sleep(300);
			for (int j = 0; j < HEIGHT; j++)
			{
				gotoxy(3, 3 + j);
				cout << "                           ";
				Sleep(60);
			}
			return true;
		}
	return false;
}

// 미노 내려놓기
bool drop_mino(int nowMino)
{
	for (int i = 0; i < 4;i++)
	{
		for (int j = 3;j >= 0;j--)
			if (mino[nowMino][degree][j][i] == 1)
			{
				if (field[pos_y + j + 1][pos_x + i] == "□" || field[pos_y + j + 1][pos_x + i] == "■")
					return true;
				break;
			}
	}
	return false;
}


// 내려오는 미노 표현
void draw_mino(int nowMino)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (mino[nowMino][degree][i][j] == 1)
				field[pos_y + i][pos_x + j] = "□";
}

// 기존 내려오는 미노 삭제
void delete_mino(int nowMino)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (mino[nowMino][degree][i][j] == 1)
				field[pos_y + i][pos_x + j] = "  ";
}

// 미노가방 초기화
void mino_bag_init(vector<bool>& minoBag)
{
	for (int i = 0;i < NUM_MINO;i++)
	{
		minoBag[i] = true;
	}
}

// 미노가방에서 미노 꺼내기
int new_mino(vector<bool>& minoBag)
{
	while (true)
	{
		int temp = rand() % 7;

		if (temp == 0 && minoBag[0] == true) // I미노
			return 0;
		else if (temp == 1 && minoBag[1] == true) // O미노
			return 1;
		else if (temp == 2 && minoBag[2] == true) // O미노
			return 2;
		else if (temp == 3 && minoBag[3] == true) // O미노
			return 3;
		else if (temp == 4 && minoBag[4] == true) // O미노
			return 4;
		else if (temp == 5 && minoBag[5] == true) // O미노
			return 5;
		else if (temp == 6 && minoBag[6] == true) // O미노
			return 6;
	}
}

// 인피니트 카운트
void infinite_rule(int nowMino, int& real_time, int count, int& infinite_count)
{
	if (drop_mino(nowMino) && infinite_count < 16)
	{
		real_time = count - 30;
		infinite_count++;
	}
}


// 키보드 입력 체크
void key_check(int nowMino, bool& minoFlag, bool& switchFlag, int &real_time, int count, int &infinite_count)
{
	int keyInput = 0;

	if (_kbhit())
	{
		keyInput = _getch();
		switch (keyInput)
		{
		case LEFT:
			if (move_left(nowMino))
			{
				delete_mino(nowMino);
				pos_x--;
				infinite_rule(nowMino, real_time, count, infinite_count);
			}
			break;

		case RIGHT:
			if (move_right(nowMino))
			{
				delete_mino(nowMino);
				pos_x++;	
				infinite_rule(nowMino, real_time, count, infinite_count);
			}
			break;

		case UP:
			if (minoRotation(nowMino, degree, pos_x, pos_y, field))
			{
				delete_mino(nowMino);
				if (degree == 3) degree = 0;
				else degree++;
				infinite_rule(nowMino, real_time, count, infinite_count);
			}
			break;

		case DOWN:
			if (move_down(nowMino))
			{
				delete_mino(nowMino);
				pos_y++;
				switchFlag = drop_mino(nowMino);
			}
			else
			minoFlag = false;
			infinite_count = 0;
			real_time = 0;
			break;

		case SPACE:
			delete_mino(nowMino);
			while (true)
			{
				if (move_down(nowMino))
					pos_y++;
				switchFlag = drop_mino(nowMino);
				if (switchFlag)
				{
					real_time = count - 1;
					break;
				}
			}
			break;
		}
	}
}


int main()
{
	while (true)
	{
		// 커서감추기
		CursorView(0);

		// 필드초기화
		field_init();

		// 7블럭 1세트
		vector<bool> minoBag(7);
		mino_bag_init(minoBag);

		// 주머니 소비 카운트
		char minoBagCount = NUM_MINO;

		// 미노 랜덤시드 초기화
		srand((unsigned int)time(0));

		// 현재 내려오는 블럭유무 판단
		bool minoFlag = false;

		// 블럭이 바닥에 닿았는지 판단하는 중간스위치
		bool switchFlag = false;

		// 현재 내려오는 블럭 종류
		int nowMino;

		// 블럭 시간
		int real_time = 0;
		int level = 0;
		int speed = 60 - level * 6;

		// 인피니티 룰 카운트
		int infinite_count = 0;

		while (true)
		{
			// 난이도 설정
			level = score / 5;
			speed = 60 - level * 6;

			// 미노가방에 미노가 남아있는가?
			if (minoBagCount == 0)
			{
				minoBagCount = NUM_MINO;
				mino_bag_init(minoBag);

			}

			// 현재 내려오는 미노가 없다면 새로 생성.
			if (!minoFlag)
			{
				minoFlag = true;
				minoBagCount--;
				nowMino = new_mino(minoBag);
				minoBag[nowMino] = false;
				degree = 0;
				pos_x = 4;
				pos_y = 0;
			}

			// 화면 초기화 주기
			Sleep(1);
			real_time++;

			// 시간에 따른 미노이동
			if (real_time >= speed)
			{

				if (switchFlag && drop_mino(nowMino))
				{
					minoFlag = false;
					switchFlag = false;
					real_time = 0;
				}
				else if (!drop_mino(nowMino))
				{
					delete_mino(nowMino);
					pos_y++;
					infinite_count = 0;
					real_time = 0;
				}

			}

			// 키입력 확인
			key_check(nowMino, minoFlag, switchFlag, real_time, speed, infinite_count);

			// 그리기
			draw_mino(nowMino);
			for (int i = 0;i < HEIGHT;i++)
			{
				gotoxy(3, 3 + i);
				for (int j = 0;j < WEIGHT;j++)
					cout << field[i][j];
			}

			// 스코어보드
			gotoxy(33, 7);
			cout << "Your score: " << score << '\n';
			gotoxy(33, 8);
			cout << "Game Level: " << level << '\n';

			// 미노 내려놓기
			if (real_time >= speed && !switchFlag)
			{
				switchFlag = drop_mino(nowMino);
				real_time = 0;
			}



			// 완성 줄 체크
			if (!minoFlag)
				complete_check();

			if (!minoFlag)
				if (gameover())
					break;
		}

		system("cls");
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□□□■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□□■□□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□■□□□□□□□□□■■■□□□■■■■□■■■□□□□■■■□□\n";
		cout << "□■□□■■■■□□■□□□■□□■□□□■□□□■□□■□□□■□\n";
		cout << "□■□□□□□■□□□□□□■□□■□□□■□□□■□□■□□□■□\n";
		cout << "□■□□□□□■□□□■■■■□□■□□□■□□□■□□■■■■■□\n";
		cout << "□■□□□□□■□□■□□□■□□■□□□■□□□■□□■□□□□□\n";
		cout << "□□■□□□■■□□■□□■■□□■□□□■□□□■□□■□□□■□\n";
		cout << "□□□■■■□■□□□■■□■□□■□□□■□□□■□□□■■■□□\n";
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□□□□□□□□■■■□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□□□□□□□■□□□■□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□□□□□□■□□□□□■□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□□□□□□■□□□□□■□□■□□□■□□■■■□□□■□■□□□\n";
		cout << "□□□□□□■□□□□□■□□■□□□■□■□□□■□□■■□□□□\n";
		cout << "□□□□□□■□□□□□■□□■□□□■□■□□□■□□■□□□□□\n";
		cout << "□□□□□□■□□□□□■□□□■□■□□■■■■■□□■□□□□□\n";
		cout << "□□□□□□■□□□□□■□□□■□■□□■□□□□□□■□□□□□\n";
		cout << "□□□□□□□■□□□■□□□□□■□□□■□□□■□□■□□□□□\n";
		cout << "□□□□□□□□■■■□□□□□□■□□□□■■■□□□■□□□□□\n";
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n\n";
		cout << "Your Score : " << score << '\n';
		cout << "다시하기 : R / 그만하기 : Q\n";

		while (true)
		{
			if (_kbhit())
			{
				int keyInput = 0;
				keyInput = _getch();

				if (keyInput == QUIT || keyInput == quit)
					return 0;
				else if (keyInput == RETRY or keyInput == retry)
				{
					system("cls");
					break;
				}
			}
		}
	}

	return 0;
}
