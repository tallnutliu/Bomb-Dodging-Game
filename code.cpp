#include <bits/stdc++.h>
#include <windows.h>
#include <Winuser.h>
#include <conio.h>
#define rep1(i,a,b) for (int i = (a);i <= (b);i++)
#define KEYDOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)
using namespace std;
int score,life,location,stage,jiange,tim,tim2;
struct bullet
{
	int x;
	int y;
	int speed;
	int damage;
	bool is_huixie;
};
vector<bullet> bullets;
char c[50][50];
void reprint()
{
	system("cls");
	//40
	cout << "Your score: " << score << "\nYour HP: " << life << "\n|----------------------------------------|\n";
	rep1(i,0,39)
		rep1(j,0,39)
			c[i][j] = ' ';
	for (auto p : bullets)
		if (p.is_huixie)
			c[p.x][p.y] = 'H';
		else
			c[p.x][p.y] = 'O';
	rep1(i,0,38)
	{
		cout << '|';
		rep1(j,0,39)
			cout << c[i][j];
		cout << "|\n";
	}
	cout << '|';
	rep1(j,0,39)
		if (j != location)
			cout << c[39][j];
		else
			cout << 'A';
	cout << "|\n|";
	rep1(i,0,39)
		cout << '-';
	cout << '|';
}
void spawn_bullet()
{
	int rd = rand() % 10;
	int xx = rand() % 40;
	bullet tmp;
	if (rd <= 2)
		tmp = {0,xx,1,1,0};
	else if (rd <= 5)
		tmp = {0,xx,2,1,0};
	else if (rd <= 8)
		tmp = {0,xx,1,2,0};
	else
		tmp = {0,xx,2,1,1};
	bullets.push_back(tmp);
	reprint();
}
void move_bullet()
{
	for (auto& p : bullets)
		p.x += p.speed;
	for (auto p : bullets)
		if (p.x == 40 && abs(p.y - location) <= 1)
		{
			if (p.is_huixie)
				life += p.damage;
			else
				life -= p.damage;
			if (life <= 0)
			{
				system("cls");
				cout << "Game Over.\n";
				cout << "Your score is: " << score << ".\n";
				while (true)
					Sleep(1000);
			}
		}
	rep1(i,0,(int)(bullets.size()) - 1)
		if (bullets[i].x > 40)
		{
			bullets.erase(bullets.begin() + i);
			score++;
		}
	reprint();
}
void move_character()
{
	if ((KEYDOWN(37) || KEYDOWN(65)) && location > 0)
		location--;
	else if ((KEYDOWN(39) || KEYDOWN(68)) && location < 39)
		location++;
	reprint();
}
int main()
{
	cout << "Please transfer to full screen mode to play this game.\nPress any key to continue...";
	getch();
	srand(time(0));
	life = 10;
	tim = clock();
	tim2 = tim;
	while (true)
	{
		if (score <= 10)
			stage = 1;
		else if (score <= 40)
			stage = 2;
		else if (score <= 100)
			stage = 3;
		else
			stage = 4;
		if (stage == 1)
			jiange = 350;
		else if (stage == 2)
			jiange = 275;
		else if (stage == 3)
			jiange = 200;
		else
			jiange = 125;
		move_character();
		if (clock() > tim2 + 100)
		{
			move_bullet();
			tim2 = clock();
		}
		if (clock() >  tim + jiange)
		{
			spawn_bullet();
			tim = clock();
		}
		Sleep(10);
	}
}
