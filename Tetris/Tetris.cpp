#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <chrono>

const int WEIGHT = 12;
const int HEIGHT = 25;
const int NUM_MINO = 7;
const int LEFT = 75;
const int UP = 72;
const int RIGHT = 77;
const int DOWN = 80;
const int SPACE = 32;


using namespace std;

// 배경필드
vector<vector<string>> field(HEIGHT, vector<string>(WEIGHT, ""));

// 미노 모양
vector<vector<vector<vector<char>>>> mino{
	//I미노
	{{{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,1},
	  {0,0,0,0}},
	 {{0,0,1,0},
	  {0,0,1,0},
	  {0,0,1,0},
	  {0,0,1,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,1},
	  {0,0,0,0}},
	 {{0,1,0,0},
	  {0,1,0,0},
	  {0,1,0,0},
	  {0,1,0,0}}
	 },

	  //O미노
	{{{0,0,0,0},
	  {0,1,1,0},
	  {0,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,1,0},
	  {0,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,1,0},
	  {0,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,1,0},
	  {0,1,1,0},
	  {0,0,0,0}}},

	//Z미노
	{{{0,0,0,0},
	  {1,1,0,0},
	  {0,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,0,1,0},
	  {0,1,1,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,0,0},
	  {0,1,1,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {1,1,0,0},
	  {1,0,0,0}}},


    //S미노
    {{{0,0,0,0},
   	  {0,1,1,0},
	  {1,1,0,0},
	  {0,0,0,0}},
     {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,1,0},
	  {0,0,1,0}},
     {{0,0,0,0},
	  {0,0,0,0},
	  {0,1,1,0},
	  {1,1,0,0}},
     {{0,0,0,0},
	  {1,0,0,0},
	  {1,1,0,0},
	  {0,1,0,0}}},

	//J미노
	{{{0,0,0,0},
	  {1,0,0,0},
	  {1,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,1,0},
	  {0,1,0,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,0},
	  {0,0,1,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,0,0},
	  {1,1,0,0}}},

	 //L미노
    {{{0,0,0,0},
	  {0,0,1,0},
	  {1,1,1,0},
	  {0,0,0,0}},
     {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,0,0},
	  {0,1,1,0}},
     {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,0},
	  {1,0,0,0}},
     {{0,0,0,0},
	  {1,1,0,0},
	  {0,1,0,0},
	  {0,1,0,0}}},

	//T미노
	{{{0,0,0,0},
	  {0,1,0,0},
	  {1,1,1,0},
	  {0,0,0,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {0,1,1,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,0,0,0},
	  {1,1,1,0},
	  {0,1,0,0}},
	 {{0,0,0,0},
	  {0,1,0,0},
	  {1,1,0,0},
	  {0,1,0,0}}}
};

// 현재 내려오는 블럭 각도
int degree;

// 현재의 블럭기준점 위치
int pos_x;
int pos_y;

// 스코어
int score = 0;

// 커서숨기기
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 커서이동
void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

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

bool move_down(int nowMino)
{
	for (int i = 0; i <= 3; i++)
		for (int j = 3;j >= 0;j--)
			if (mino[nowMino][degree][i][j] == 1)
			{
				if (field[pos_y + i + 1][pos_x + j] != "  ")
					return false;
				break;
			}
	return true;
}

bool gameover()
{
	for (int i = 1; i < WEIGHT - 1; i++)
		if (field[4][i] != "  ")
			return false;
	return true;
}

// 미노 내려놓기
void drop_mino(int nowMino, bool& minoFlag)
{
	for (int i = 0; i < 4;i++)
	{
		for (int j = 3;j >= 0;j--)
			if (mino[nowMino][degree][j][i] == 1)
			{
				if (field[pos_y + j + 1][pos_x + i] == "□" || field[pos_y + j + 1][pos_x + i] == "■")
					minoFlag = false;
				break;
			}
		if (!minoFlag)
		{
			// 게임오버 체크
			if (gameover())
				break;
			break;
		}
	}
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

void key_check(int nowMino, bool& minoFlag)
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
			}
			break;

		case RIGHT:
			if (move_right(nowMino))
			{
				delete_mino(nowMino);
				pos_x++;
			}
			break;

		case UP:
			delete_mino(nowMino);
			if (degree == 3) degree = 0;
			else degree++;
			break;

		case DOWN:
			if (move_down(nowMino))
			{
				delete_mino(nowMino);
				pos_y++;
			}
			break;

		case SPACE:
			delete_mino(nowMino);
			while (true)
			{
				if (move_down(nowMino))
					pos_y++;
				drop_mino(nowMino, minoFlag);
				if (!minoFlag) break;
			}
			break;
		}
	}
}


int main()
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

	// 현재 내려오는 블럭 종류
	int nowMino;

	// 블럭 시간
	auto time1 = std::chrono::steady_clock::now();
	auto time2 = std::chrono::steady_clock::now();

	while (true)
	{
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
			time1 = std::chrono::steady_clock::now(); // 블럭 생성시 시간 저장
		}

		// 키입력 확인
		key_check(nowMino, minoFlag);
		
		// 화면 초기화 주기
		Sleep(1);

		// 시간에 따른 미노이동
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - time1);
		if (elapsed.count() % 1000 < 10)
		{
			delete_mino(nowMino);
			pos_y++;
		}
		// 그리기
		draw_mino(nowMino);
		for (int i = 0;i < HEIGHT;i++)
		{
			gotoxy(3, 3 + i);
			for (int j = 0;j < WEIGHT;j++)
				cout << field[i][j];
		}
		gotoxy(33, 7);
		cout << score;

		// 미노 내려놓기
		drop_mino(nowMino, minoFlag);

		// 완성 줄 체크
		if (!minoFlag)
			complete_check();
		
		
	}

	system("cls");
	gotoxy(10, 10);
	cout << "Game Over" << endl;

	return 0;
}
