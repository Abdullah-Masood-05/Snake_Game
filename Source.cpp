#include<iostream>
#include<iomanip>
#include<conio.h>
#include<ctime>
#include<windows.h>
#include<mmsystem.h>
#include<fstream>
using namespace std;
#define YELLOW 12;
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void goto_row_col(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
enum DIRECTION { UP, DOWN, LEFT, RIGHT };
struct position {
	int ri;
	int ci;
};
struct snake {
	position* ps;
	char sym;
	int size;
	DIRECTION dir;
	int score;
	int LEFTKEY, RIGHTKEY, UPKEY, DOWNKEY;
	string p_name;
};
struct food {
	position fp;
	bool is_alive;
	int score;
	char sym;
};
bool is_legaal_coordianate(position p, snake& s, snake& s2, snake& s3, snake& s4)
{
	for (int i = 0; i < s.size; i++)
	{
		if (s.ps[i].ri == p.ri && s.ps[i].ci == p.ci)
			return false;
	}
	for (int i = 0; i < s2.size; i++)
	{
		if (s2.ps[i].ri == p.ri && s2.ps[i].ci == p.ci)
			return false;
	}
	for (int i = 0; i < s3.size; i++)
	{
		if (s3.ps[i].ri == p.ri && s3.ps[i].ci == p.ci)
			return false;
	}
	for (int i = 0; i < s4.size; i++)
	{
		if (s4.ps[i].ri == p.ri && s4.ps[i].ci == p.ci)
			return false;
	}
	return true;
}
void generate_food(food& f, int h, int w, snake& s, snake& s2, snake& s3, snake& s4)
{
	srand(time(0));
	do {
		f.fp.ri = rand() % h ;
		f.fp.ci = rand() % w ;
	} while (!is_legaal_coordianate(f.fp, s, s2, s3, s4));
	f.is_alive = true;
	f.score = 1;
}
void display_food(food f)
{
	SetClr(4);
	goto_row_col(f.fp.ri, f.fp.ci);
	cout << f.sym;
	SetClr(15);
}
bool food_eaten(snake& s, food f)
{
	return s.ps[0].ri == f.fp.ri && s.ps[0].ci == f.fp.ci;
}
void init(snake& s, snake& s2, snake& s3, snake& s4, food& f, int height, int width)
{
	s.ps = new position[3];
	s2.ps = new position[3];
	s3.ps = new position[3];
	s4.ps = new position[3];
	for (int i = 0; i < 3; i++)
	{
		s.ps[i].ri = height / 2;
		s.ps[i].ci = width / 2 - i;
		s2.ps[i].ri = height / 2 + 4;
		s2.ps[i].ci = width / 2 - i;
		s3.ps[i].ri = height / 2 - 4;
		s3.ps[i].ci = width / 2 - i;
		s4.ps[i].ri = height / 2 - 8;
		s4.ps[i].ci = width / 2 - i;
	}
	s.p_name = "Rias";
	s.score = 0;
	s.size = 3;
	s.sym = -37;
	s.dir = RIGHT;
	s.RIGHTKEY = 77, s.LEFTKEY = 75, s.UPKEY = 72, s.DOWNKEY = 80;
	s2.p_name = "Rayan";
	s2.score = 0;
	s2.size = 3;
	s2.sym = -37;
	s2.dir = RIGHT;
	s2.RIGHTKEY = 100, s2.LEFTKEY = 97, s2.UPKEY = 119, s2.DOWNKEY = 115;
	s3.p_name = "Abd";
	s3.score = 0;
	s3.size = 3;
	s3.sym = -37;
	s3.dir = RIGHT;
	s3.RIGHTKEY = 108, s3.LEFTKEY = 106, s3.UPKEY = 105, s3.DOWNKEY = 107;
	s4.p_name = "Bazil";
	s4.score = 0;
	s4.size = 3;
	s4.sym = -37;
	s4.dir = RIGHT;
	s4.RIGHTKEY = 104, s4.LEFTKEY = 102, s4.UPKEY = 116, s4.DOWNKEY = 103;
	generate_food(f, height-2, width-2, s, s2, s3, s4);
}
void draw_boarder(int color)
{
	for (int r = 0; r < 80; r++)
		for (int c = 0; c <= 74; c++)
			if (r == 0 || c == 0 || r == 79 || c == 74)
			{
				SetClr(color);
				goto_row_col(r, c);
				cout << char(-37);
			}
}
void expand_snake(snake& s)
{
	position* hp = new position[s.size + 1];
	for (int i = 0; i < s.size; i++)
	{
		hp[i + 1] = s.ps[i];
	}
	hp[0] = hp[1];
	s.ps = hp;
	s.size++;
}
void move_snake(snake s, int height, int width)
{
	for (int i = s.size; i - 1 >= 0; i--)
	{
		s.ps[i] = s.ps[i - 1];
	}
	switch (s.dir)
	{
	case UP:
		s.ps[0].ri--;
		if (s.ps[0].ri == 1)
			s.ps[0].ri = height - 2;
		break;
	case DOWN:
		if (s.ps[0].ri == height - 2)
			s.ps[0].ri = 0;
		s.ps[0].ri++;
		break;
	case LEFT:
		if (s.ps[0].ci == 1)
			s.ps[0].ci = width + 1;
		s.ps[0].ci--;
		break;
	case RIGHT:
		if (s.ps[0].ci == width)
			s.ps[0].ci = 0;
		s.ps[0].ci++;
		break;
	}
}
void change_direction(snake& s, char key)
{
	if (key == s.LEFTKEY)
		if (s.dir != RIGHT)
		{
			s.dir = LEFT;
		}
	if (key == s.RIGHTKEY)
		if (s.dir != LEFT)
		{
			s.dir = RIGHT;
		}
	if (key == s.DOWNKEY)
		if (s.dir != UP)
		{
			s.dir = DOWN;
		}
	if (key == s.UPKEY)
		if (s.dir != DOWN)
		{
			s.dir = UP;
		}
}
void display_snake(const snake& s, int color)
{
	SetClr(color);
	for (int i = 0; i < s.size; i++)
	{
		if (i == 0)
		{
			goto_row_col(s.ps[i].ri, s.ps[i].ci);
			cout << char(1);
		}
		else
		{
			goto_row_col(s.ps[i].ri, s.ps[i].ci);
			cout << s.sym;
		}
	}
	SetClr(15);
}
void erase_snake(const snake& s)
{
	for (int i = 0; i < s.size; i++)
	{
		SetClr(0);
		goto_row_col(s.ps[i].ri, s.ps[i].ci);
		cout << s.sym;
	}
}
void self_destruct(const snake& s, bool& s_kill)
{
	for (int i = 1; i < s.size; i++)
		if (s.ps[0].ri == s.ps[i].ri && s.ps[0].ci == s.ps[i].ci)
			s_kill = true;
}
void kill_snake(const snake& s, const snake& s2, const snake& s3, const snake& s4, bool& s_kill, bool& s2_kill, bool& s3_kill, bool& s4_kill)
{

	for (int i = 0; i < s.size; i++)
	{
		if ((s2.ps[0].ri == s.ps[i].ri) && (s2.ps[0].ci == s.ps[i].ci))
			s_kill = true;
		if ((s3.ps[0].ri == s.ps[i].ri) && (s3.ps[0].ci == s.ps[i].ci))
			s_kill = true;
		if ((s4.ps[0].ri == s.ps[i].ri) && (s4.ps[0].ci == s.ps[i].ci))
			s_kill = true;
	}
	for (int i = 0; i < s2.size; i++)
	{
		if ((s.ps[0].ri == s2.ps[i].ri) && (s.ps[0].ci == s2.ps[i].ci))
			s2_kill = true;
		if ((s3.ps[0].ri == s2.ps[i].ri) && (s3.ps[0].ci == s2.ps[i].ci))
			s2_kill = true;
		if ((s4.ps[0].ri == s2.ps[i].ri) && (s4.ps[0].ci == s2.ps[i].ci))
			s2_kill = true;
	}
	for (int i = 0; i < s3.size; i++)
	{
		if ((s.ps[0].ri == s3.ps[i].ri) && (s.ps[0].ci == s3.ps[i].ci))
			s3_kill = true;
		if ((s2.ps[0].ri == s3.ps[i].ri) && (s2.ps[0].ci == s3.ps[i].ci))
			s3_kill = true;
		if ((s4.ps[0].ri == s3.ps[i].ri) && (s4.ps[0].ci == s3.ps[i].ci))
			s3_kill = true;
	}
	for (int i = 0; i < s4.size; i++)
	{
		if ((s.ps[0].ri == s4.ps[i].ri) && (s.ps[0].ci == s4.ps[i].ci))
			s4_kill = true;
		if ((s2.ps[0].ri == s4.ps[i].ri) && (s2.ps[0].ci == s4.ps[i].ci))
			s4_kill = true;
		if ((s3.ps[0].ri == s4.ps[i].ri) && (s3.ps[0].ri == s4.ps[i].ci))
			s4_kill = true;
	}
	self_destruct(s, s_kill);
	self_destruct(s2, s2_kill);
	self_destruct(s3, s3_kill);
	self_destruct(s4, s4_kill);
}
int main()
{
	int height = 80, width = 73, hr = 0, min = 0, sec = 0;
	char ch;
	bool s_kill = false, s2_kill = false, s3_kill = false, s4_kill = false;
	snake s, s2, s3, s4;
	food f;
	init(s, s2, s3, s4, f, height, width);
	draw_boarder(7);
	display_food(f);
	goto_row_col(0, 100);
	cout << "score_player_1: " << s.score;
	goto_row_col(1, 100);
	cout << "score_player_2: " << s2.score;
	goto_row_col(2, 100);
	cout << "score_player_3: " << s3.score;
	goto_row_col(3, 100);
	cout << "score_player_4: " << s4.score;
	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				change_direction(s, ch);
			}
			else if (ch == 100 || ch == 119 || ch == 115 || ch == 97)
				change_direction(s2, ch);
			else if (ch == 108 || ch == 106 || ch == 105 || ch == 107)
				change_direction(s3, ch);
			else
				change_direction(s4, ch);
		}

		Sleep(100);

		erase_snake(s);
		if (!s_kill)
		{
			move_snake(s, height, width);
			display_snake(s, 2);
		}
		kill_snake(s, s2, s3, s4, s_kill, s2_kill, s3_kill, s4_kill);
		erase_snake(s2);
		if (!s2_kill)
		{
			move_snake(s2, height, width);
			display_snake(s2, 9);
		}
		kill_snake(s, s2, s3, s4, s_kill, s2_kill, s3_kill, s4_kill);
		erase_snake(s3);
		if (!s3_kill)
		{
			move_snake(s3, height, width);
			display_snake(s3, 5);
		}
		kill_snake(s, s2, s3, s4, s_kill, s2_kill, s3_kill, s4_kill);
		erase_snake(s4);
		if (!s4_kill)
		{
			move_snake(s4, height, width);
			display_snake(s4, 12);
		}
		kill_snake(s, s2, s3, s4, s_kill, s2_kill, s3_kill, s4_kill);
		if (food_eaten(s, f))
		{
			PlaySound(TEXT("Bite sound effect.wav"), NULL, SND_SYNC);
			generate_food(f, height-2, width-2, s, s2, s3, s4);
			display_food(f);
			expand_snake(s);
			goto_row_col(0, 100);
			s.score++;
			cout << "score_player_1: " << s.score;
		}
		else if (food_eaten(s2, f))
		{
			PlaySound(TEXT("Bite sound effect.wav"), NULL, SND_SYNC);
			generate_food(f, height-2, width-2, s, s2, s3, s4);
			display_food(f);
			expand_snake(s2);
			goto_row_col(1, 100);
			s2.score++;
			cout << "score_player_2: " << s2.score;
		}
		else if (food_eaten(s3, f))
		{
			PlaySound(TEXT("Bite sound effect.wav"), NULL, SND_SYNC);
			generate_food(f, height-2, width-2, s, s2, s3, s4);
			display_food(f);
			expand_snake(s3);
			goto_row_col(2, 100);
			s3.score++;
			cout << "score_player_3: " << s3.score;
		}
		else if (food_eaten(s4, f))

		{
			PlaySound(TEXT("Bite sound effect.wav"), NULL, SND_SYNC);
			generate_food(f, height-2, width-2, s, s2, s3, s4);
			display_food(f);
			expand_snake(s4);
			s4.score++;
			goto_row_col(3, 100);
			cout << "score_player_4: " << s4.score;
		}
	}

}