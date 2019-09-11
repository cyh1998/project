﻿// Retro-Snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>
using namespace std;

/*** 光标定位 ***/
//定义了一个句柄变量，将其赋值为 GetStdHandle((STD_OUTPUT_HANDLE))，即标准输出的句柄
//HANDLE GetStdHandle( DWORD nStdHandle );是一个Windows API函数。
//它用于从一个特定的标准设备（标准输入、标准输出或标准错误）中取得一个句柄（用来标识不同设备的数值）。
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
//coord用来记录坐标
COORD coord;

void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	//SetConsoleCursorPosition(hout,coord):设置控制台光标坐标，
	//参数就是句柄hout，坐标coord，把标准输出的句柄传给函数，就可以把光标定位
	//在对应位置了（左上角的位置是0，0然后向左，向下延伸）
	SetConsoleCursorPosition(hout, coord);
};

/*** 隐藏光标 ***/
void hide()
{
	//定义光标信息结构体变量cursor_info，{光标厚度,是否可见}
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	//设置控制台光标信息(句柄,光标变量)
	SetConsoleCursorInfo(hout, &cursor_info);
}

/*** 生成随机数 ***/
double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}

/*** 定义地图的长宽，蛇的坐标，长度，方向，食物的位置 ***/
int m,n; //地图长宽m,n

//结构体node,包含坐标x,y
//定义了蛇身体的每一个坐标,snake[0]是蛇头,其余是身体
struct node
{
	int x, y;
}snake[1000];

int snake_length, dir; //蛇的长度snake_length,方向的第一个参数dir(上0下1左2右3)
node food;  //食物
int direct[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };  //方向(左右上下)

/*** 输出墙 ***/
//即输出地图的边框
void print_wall()
{
	cout << " ";
	for (int i = 1; i <= n; i++)
		cout << "-";
	cout << endl;
	for (int j = 0; j <= m - 1; j++)
	{
		cout << "|";
		for (int i = 1; i <= n; i++) cout << " ";
		cout << "|" << endl;
	}
	cout << " ";
	for (int i = 1; i <= n; i++)
		cout << "-";
}

/*** 首次输出蛇，其中snake[0]代表头 ***/
void print_snake()
{
	locate(snake[0].x, snake[0].y);
	cout << "@";
	for (int i = 1; i <= snake_length - 1; i++)
	{
		locate(snake[i].x, snake[i].y);
		cout << "*";
	}
}

/*** 判断是否撞墙或者自撞 ***/
bool is_correct()
{
	//撞墙,头坐标超出墙
	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == m + 1 || snake[0].y == n + 1) return false;
	//自撞,头坐标在身体上
	for (int i = 1; i <= snake_length - 1; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) return false;
	}
	return true;
}

/*** 随机生成并输出食物位置 ***/
bool print_food()
{
	srand((unsigned)time(0)); //种子函数
	bool e;
	while (1)
	{
		e = true;
		//i:随机生成食物的横坐标,j:随机生成食物的纵坐标
		//random(0,m)、random(0,n)保证食物在墙内
		int i = (int)random(0, m) + 1, j = (int)random(0, n) + 1;
		food.x = i; food.y = j;
		//判断随机生成的食物是否在蛇的身体上
		//如果在,就重新生成
		for (int k = 0; k <= snake_length - 1; k++)
		{
			if (snake[k].x == food.x && snake[k].y == food.y)
			{
				e = false; break;
			}
		}
		if (e) break;
	}
	//输出食物
	locate(food.x, food.y);
	cout << "$";
	return true;
}

/*** 蛇的前进 ***/
bool go_ahead()
{
	node temp;   //定义了坐标结构体对象temp
	bool e = false;  //判断是否吃到食物的变量e,false即没有,true即有
	temp = snake[snake_length - 1];   //将temp定位到蛇的尾部
	//循环,让蛇前进
	for (int i = snake_length - 1; i >= 1; i--)
		snake[i] = snake[i - 1];
	//蛇头按当前方向前进一格
	snake[0].x += direct[dir][0];
	snake[0].y += direct[dir][1];
	//蛇头前进一格,会留下一个@字符占用身体,输出*字符代替@
	locate(snake[1].x, snake[1].y);
	cout << "*";

	/*** 吃到了食物 ***/
	if (snake[0].x == food.x && snake[0].y == food.y)
	{
		snake_length++;
		e = true;
		snake[snake_length - 1] = temp;
	}
	/*** 输出此时蛇状态 ***/
	//没有吃到食物时,将蛇前进在尾部留下一个*字符,用‘ ’代替,避免蛇身体无限延长
	if (!e)
	{
		locate(temp.x, temp.y);
		cout << " ";
	}
	else //吃到食物了,就继续再生成食物
		print_food();
	locate(snake[0].x, snake[0].y);
	cout << "@";
	/*** 如果自撞 ***/
	if (!is_correct())
	{
		//执行系统命令,system("cls")就是执行“清屏”命令
		system("cls");
		cout << "--------------------贪吃蛇---------------------" << endl;
		cout << "                   游戏结束                    " << endl;
		cout << "You lose!" << endl << "Length: " << snake_length << endl;
		return false;
	}
	return true;
}

/*** 主函数 ***/
int main()
{
	cout << "--------------------贪吃蛇---------------------" << endl;
	cout << "请先输入两个数,表示地图大小.要求长宽均不小于10." << endl;
	cout << "请注意窗口大小,以免发生错位.建议将窗口调为最大." << endl;
	//cout << "请选择难度.请在1-10中输入1个数,1最简单,10则最难" << endl;
	cout << "然后进入游戏画面,以方向键控制方向.祝你游戏愉快!" << endl;
	cout << "-----------------------------------------------" << endl;
	cin >> m >> n;
	if (m < 10 || n < 10 || m>25 || n>40)
	{
		cout << "ERROR" << endl;
		//系统命令：暂停
		system("pause");
		return 0;
	}
	/*int hard;
	cin >> hard;
	if (hard<=0 || hard>100)
	{
		cout << "ERROR" << endl;
		system("pause");
		return 0;
	}*/
	/*** 数据全部初始化，包括蛇长，位置，方向 ***/
	snake_length = 5;

	clock_t a,b;

	char ch; //接受键盘输入的字符
	double hard_len;
	for (int i = 0; i <= 4; i++)
	{
		snake[i].x = 1;
		snake[i].y = 5 - i;
	}
	dir = 3; //初始化方向向右
	/*** 输出初始地图，蛇与食物 ***/
	system("cls");    //清屏
	hide();           //隐藏光标
	print_wall();     //输出墙
	print_food();     //输出食物
	print_snake();    //输出蛇
	locate(m + 2, 0);
	cout << "Now length: ";   //显示当前分数
	/*** 开始游戏 ***/
	while (1)
	{
		/*** 难度随长度增加而提高 ***/
		hard_len = (double)snake_length / (double)(m*n);
		/*** 调节时间，单位是ms ***/
		a = clock();
		while (1)
		{
			b = clock();
			if (b - a >= (int)(400 - 30 * 1)*(1 - sqrt(hard_len))) break;
		}
		/*** 接受键盘输入的上下左右，并以此改变方向 ***/
		if (_kbhit())   //kbhit()非阻塞地响应键盘输入事件
		{
			ch = _getch();
			if (ch == -32)
			{
				ch = _getch();
				switch (ch)
				{
				case 72://上
					if (dir == 2 || dir == 3)
						dir = 0;  //如果是左右方向,就改为向上
					break;
				case 80://下
					if (dir == 2 || dir == 3)
						dir = 1;  //同理
					break;
				case 75://左
					if (dir == 0 || dir == 1)
						dir = 2;  //同理
					break;
				case 77://右
					if (dir == 0 || dir == 1)
						dir = 3;  //同理
					break;
				}
			}
		}
		/*** 前进 ***/
		if (!go_ahead()) break; //每次前进一下,判断是否吃到食物,或者撞墙/自撞
		/*** 在最后输出此时长度 ***/
		locate(m + 2, 12);
		cout << snake_length;  //输出当前的长度,即分数
	}
	system("pause");
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
