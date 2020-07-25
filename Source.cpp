#include<iostream>
#include<windows.h>
#include<time.h>
#include<ctime>
#include<stdlib.h>
#include<vector>
#include<conio.h>
using namespace std;
int score = 0;
const int hight = 20;
const int width = 100;
COORD ori = { 0,0 };
vector<COORD> pos_vect;
class food
{
private:
	COORD food_pos;
public:
	food()
	{
		get_food();
	}
	COORD get_pos()
	{
		return food_pos;
	}
	void get_food()
	{
		food_pos.X = rand() % (width - 2) + 1;
		food_pos.Y = rand() % (hight - 2) + 1;
	}
};
food food_obj;
class snake
{
private:
	COORD snake_pos;
	int velocity;
	int length=1;
public:
	snake(COORD pos,int val) 
	{
		snake_pos.X = pos.X;
		snake_pos.Y = pos.Y;
		velocity = val;
	}
	COORD get_pos()
	{
		return snake_pos;
	}
	void move(char ch)
	{
		COORD temp = snake_pos;
		switch (ch)
		{
		case 'u':
			snake_pos.Y -= velocity;
			break;
		case 'd':
			snake_pos.Y += velocity;
			break;
		case 'l':
			snake_pos.X -= velocity;
			break;
		case 'r':
			snake_pos.X += velocity;
			break;
		default:
			break;
		}
		if (length >= 2) 
		{
			for (int i = length - 2;i > 0;i--)
			{
				pos_vect[i] = pos_vect[i - 1];
			}
			pos_vect[0] = temp;
		}
	}
	bool eaten(food& obj)
	{
		if (snake_pos.X == obj.get_pos().X && snake_pos.Y == obj.get_pos().Y)
		{
			pos_vect.push_back({0,0});
			length++;
			return true;
		}
		else
			return false;
	}
	int get_len()
	{
		return (length-1);
	}
	bool collision()
	{
		if (snake_pos.X<1 || snake_pos.X>width - 2 || snake_pos.Y<1 || snake_pos.Y>hight - 1)
			return true;
		else
			return false;
	}
	bool self_destruction()
	{
		for (auto x : pos_vect)
		{
			if (snake_pos.X == x.X && snake_pos.Y == x.Y)
				return true;
			else
				continue;
		}
		return false;
	}
};
snake snake_obj({ width / 2, hight / 2 }, 1);
void board()
{
	for (int i = 0;i < hight;i++)
	{
		cout << "\t";
		for (int j = 0;j < width;j++)
		{
			if (i == 0 || i == hight - 1)
				cout << "-";
			else if (j == 0 || j == width - 1)
				cout << "|";
			else if (i == food_obj.get_pos().Y && j == food_obj.get_pos().X)
				cout << "$";
			else if (i == snake_obj.get_pos().Y && j == snake_obj.get_pos().X)
				cout << "O";
			else
			{
				bool flag = false;
				for (int t = 0;t < snake_obj.get_len();t++) 
				{
					if (i == pos_vect[t].Y && j == pos_vect[t].X) 
					{
						flag = true;
						cout << "*";
					}
				}
				if(!flag)
					cout << " ";
			}
		}
		cout << "\n";
	}
}
int main()
{
	int mv=0;
	srand(time(0));
	system("color 84");
	food_obj.get_food();
	bool game_over = false;
	while (!game_over) 
	{
		line:board();
		cout << "score " << score << "\n";
		cout << "w for up" << "\n";
		cout << "s for down" << "\n";
		cout << "a for left" << "\n";
		cout << "d for right" << "\n";
		cout << "p for pause" << "\n";
		cout << "e for exit" << "\n";
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':snake_obj.move('u');mv = 1;break;
			case 's':snake_obj.move('d');mv = 2;break;
			case 'a':snake_obj.move('l');mv = 3;break;
			case 'd':snake_obj.move('r');mv = 4;break;
			case 'p':
				system("pause");
				break;
			case 'e':
				exit(1);
			default:break;
			}
		}
		else
		{
			if(mv == 1)
				snake_obj.move('u');
			else if (mv == 2)
				snake_obj.move('d');
			else if (mv == 3)
				snake_obj.move('l');
			else if (mv == 4)
				snake_obj.move('r');

		}
		if (snake_obj.eaten(food_obj))
		{
			score += 10;
			food_obj.get_food();
		}
		if (snake_obj.collision())
		{
			system("cls");
			game_over = true;
		}
		if (snake_obj.self_destruction())
		{
			system("cls");
			game_over = true;
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ori);
	}
	cin.get();
	return 0;
}