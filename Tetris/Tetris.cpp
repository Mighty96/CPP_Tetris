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

// ����ʵ�
vector<vector<string>> field(HEIGHT, vector<string>(WEIGHT, ""));

// �̳� ���
vector<vector<vector<vector<char>>>> mino{
	//I�̳�
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

	  //O�̳�
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

	//Z�̳�
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


    //S�̳�
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

	//J�̳�
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

	 //L�̳�
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

	//T�̳�
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

// ���� �������� �� ����
int degree;

// ������ �������� ��ġ
int pos_x;
int pos_y;

// Ŀ�������
void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// Ŀ���̵�
void gotoxy(short x, short y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �ʵ� �ʱ�ȭ
void field_init()
{
	for (int i = 0; i < HEIGHT - 1; i++)
		for (int j = 1; j < WEIGHT; j++)
			field[i][j] = "  ";
	for (int i = 0;i < HEIGHT ; i++)
	{
		field[i][0] = "��";
		field[i][WEIGHT - 1] = "��";
	}

	for (int i = 0; i < WEIGHT; i++)
	{
		field[HEIGHT - 1][i] = "��";
	}

	field[4][0] = "��";
	field[4][WEIGHT - 1] = "��";

	for (int i = 0;i < HEIGHT;i++)
	{
		gotoxy(3, i + 3);
		for (int j = 0;j < WEIGHT;j++)
			cout << field[i][j];
	}
}

// ���� ������� �Ǵ�
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

// ������ ������� �Ǵ�
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

// �̳� ��������
void drop_mino(int nowMino, bool& minoFlag)
{
	for (int i = 0; i < 4;i++)
	{
		for (int j = 3;j >= 0;j--)
			if (mino[nowMino][degree][j][i] == 1)
			{
				if (field[pos_y + j + 1][pos_x + i] == "��" || field[pos_y + j + 1][pos_x + i] == "��")
					minoFlag = false;
				break;
			}
		if (!minoFlag)
			break;
	}
}


// �������� �̳� ǥ��
void draw_mino(int nowMino)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (mino[nowMino][degree][i][j] == 1)
				field[pos_y + i][pos_x + j] = "��";
}

// ���� �������� �̳� ����
void delete_mino(int nowMino)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (mino[nowMino][degree][i][j] == 1)
				field[pos_y + i][pos_x + j] = "  ";
}

// �̳밡�� �ʱ�ȭ
void mino_bag_init(vector<bool>& minoBag)
{
	for (int i = 0;i < NUM_MINO;i++)
	{
		minoBag[i] = true;
	}
}

// �̳밡�濡�� �̳� ������
int new_mino(vector<bool>& minoBag)
{
	while (true)
	{
		int temp = rand() % 7;

		if (temp == 0 && minoBag[0] == true) // I�̳�
			return 0;
		else if (temp == 1 && minoBag[1] == true) // O�̳�
			return 1;
		else if (temp == 2 && minoBag[2] == true) // O�̳�
			return 2;
		else if (temp == 3 && minoBag[3] == true) // O�̳�
			return 3;
		else if (temp == 4 && minoBag[4] == true) // O�̳�
			return 4;
		else if (temp == 5 && minoBag[5] == true) // O�̳�
			return 5;
		else if (temp == 6 && minoBag[6] == true) // O�̳�
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
			delete_mino(nowMino);
			pos_y++;
			break;

		case SPACE:
			delete_mino(nowMino);
			while (true)
			{
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
	// Ŀ�����߱�
	CursorView(0);

	// �ʵ��ʱ�ȭ
	field_init();

	// 7�� 1��Ʈ
	vector<bool> minoBag(7);
	mino_bag_init(minoBag);

	// �ָӴ� �Һ� ī��Ʈ
	char minoBagCount = NUM_MINO;

	// �̳� �����õ� �ʱ�ȭ
	srand((unsigned int)time(0));

	// ���� �������� ������ �Ǵ�
	bool minoFlag = false;

	// ���� �������� �� ����
	int nowMino;

	// �� �ð�
	auto time1 = std::chrono::steady_clock::now();
	auto time2 = std::chrono::steady_clock::now();

	while (true)
	{
		// �̳밡�濡 �̳밡 �����ִ°�?
		if (minoBagCount == 0)
		{
			minoBagCount = NUM_MINO;
			mino_bag_init(minoBag);
			
		}

		// ���� �������� �̳밡 ���ٸ� ���� ����.
		if (!minoFlag)
		{
			minoFlag = true;
			minoBagCount--;
			nowMino = new_mino(minoBag);
			minoBag[nowMino] = false;
			degree = 0;
			pos_x = 4;
			pos_y = 0;
			time1 = std::chrono::steady_clock::now(); // �� ������ �ð� ����
		}

		// Ű�Է� Ȯ��
		key_check(nowMino, minoFlag);
		
		// ȭ�� �ʱ�ȭ �ֱ�
		Sleep(10);

		// �ð��� ���� �̳��̵�
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - time1);
		if (elapsed.count() % 1000 < 30)
		{
			delete_mino(nowMino);
			pos_y++;
		}

		// �׸���
		draw_mino(nowMino);
		for (int i = 0;i < HEIGHT;i++)
		{
			gotoxy(3, 3 + i);
			for (int j = 0;j < WEIGHT;j++)
				cout << field[i][j];
		}

		// �̳� ��������
		drop_mino(nowMino, minoFlag);

		// �ϼ� �� üũ
		for (int i = 5;i <HEIGHT - 1;i++)
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
				for (int j = 1;j < WEIGHT - 1; j++)
					for (int k = i; k >= 5;k--)
						field[k][j] = field[k - 1][j];
			}
		}
	}

	return 0;
}
