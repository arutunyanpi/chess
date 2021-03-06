// Chess.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
using namespace std;
enum figures { K = 1, Q, B, Kn, R, P, n }types;
struct Board
{
	int color;
	int type;
};
int coordinate(char x,int y)
{
	if (y > 8 || y < 1) { return(-1); }
	switch (x)
	{
	case 'A':  return 0; break;
	case 'B':  return 1; break;
	case 'C':  return 2; break;
	case 'D':  return 3; break;
	case 'E':  return 4; break;
	case 'F':  return 5; break;
	case 'G':  return 6; break;
	case 'H':  return 7; break;
	default: return (-1);
	}
}
int comparison(char x, int y, Board b[8][8], int Player_color, int &type_figure,int &raw,int &column)
{
	int x1=coordinate(x,y);
	y--;
	if ((b[y][x1].color == Player_color )&&(x1!=-1)) { type_figure = b[y][x1].type; raw = y; column = x1; return 1; }
	else { return 0; }
}
bool chek(Board b[8][8], int y,int x1, int raw, int column,int Player_color)
{
	int iter_y, iter_x;
	if ((raw - y) < 0) { iter_y = 1;}
	else
	{  
		if ((raw -y) ==0){iter_y = 0;}
		else
		{
			iter_y = -1;
		}
	}
	if ((column - x1) < 0) { iter_x = 1; }
	else
	{
		if ((column - x1) == 0) { iter_x = 0; }
		else
		{
			iter_x = -1;
		}
	}
	while (raw != y || column != x1)
	{
		raw +=iter_y ;
		column += iter_x;
		if (b[raw][column].color ==Player_color ) { cout << "Встретил припятствие " << "Столбец " << column << "Строка " << raw; return(false); }
	}
	return (true);
}
int course(char x, int y, Board(&b)[8][8], int &type_figure, int &Player_color, int &raw, int &column,int &vz_y,int &vz_x)
{
	  y--;
	  int x1=coordinate(x,y);
	  if (x1 == -1) { return 0; }
	  if (b[y][x1].color == Player_color)
	  {
		  if (type_figure != K)
	      {
		  type_figure = b[y][x1].type; raw = y; column = x1; 
		  cout << "Вы сменили фигуру " << "Тип=" << type_figure << "Строка=" << raw << "Столбец" << column;
		  return(0);
	      }
	  }//Игрок меняет фигуру 
    switch (type_figure)
	{
	 case K://Проверка хода фигурой "Король"
		 cout << "Фигура король"<<"\n";
		 if((abs(raw-y)==1||(raw-y)==0)&&(abs(column-x1)==1||(column-x1)==0))
	   {
		 if (b[y][x1].color == Player_color)
		 {
			 cout << "Выполняю замены с Королем " << "\n";
			 int color1 = b[y][x1].color;//Временные переменные для хранения значений выбранной ячейки  
			 int type1 = b[y][x1].type;
			 b[y][x1].color = Player_color;
			 b[y][x1].type = type_figure;
			 b[raw][column].type = type1;
			 b[raw][column].color = color1;
		 }
		 else
		 {   if (b[y][x1].color == -1){ cout << "Король выполняет ход" << "\n"; }else{ cout << "Король наносит удар!" << "\n"; }
			 b[y][x1].color = Player_color;
			 b[y][x1].type = type_figure;
			 b[raw][column].type = n;
			 b[raw][column].color = -1;
		 }
		return (2);
	    }
			else { cout << "Попробуйте снова " << "\n"; return(0); }
	 case Q://Проверка хода фигурой "Ферзь"
		 cout << "Фигура ферзь"<<"\n";
		 if (((abs(raw - y) == abs(column - x1)) && chek(b, y, x1, raw, column,Player_color)) ||
		 ((y == raw || x1 == column) && (x1 != column || y != raw)&&(chek(b,y,x1,raw,column,Player_color))))
	     {
		 if (b[y][x1].color == -1)
		 {
			 cout << "Ферзь выполняет ход" << "\n";
		 }else { cout << "Ферзь наносит удар!" << "\n"; }
		 b[y][x1].color = Player_color;
		 b[y][x1].type = type_figure;
		 b[raw][column].type = n;
		 b[raw][column].color = -1;
		 return(2);
	     }
			else { cout << "Попробуйте снова " << "\n"; return(0); }
	 case B://Проверка хода фигурой "Слон"
		 cout << "Фигура слон" << "\n";
		 if (((abs(raw - y) == abs(column - x1)) /*&& chek(b, y, x1, raw, column, Player_color)*/))
	 {
			 if (b[y][x1].color == -1)
			 {
				 cout << "Слон выполняет ход" << "\n";
			 }
			 else { cout << "Слон наносит удар!" << "\n"; }
		 b[y][x1].color = Player_color;
		 b[y][x1].type = type_figure;
		 b[raw][column].type = n;
		 b[raw][column].color = -1;
		 return(2);
	 }
			else { cout << "Попробуйте снова " << "\n"; return(0); }
	 
	 case Kn://Проверка хода фигурой "Конь"
		 cout << "Фигура конь" << "\n";
		 if (((abs(y - raw) == 2 || abs(x1 - column) == 2) && ((abs(y - raw) == 1 || abs(x1 - column) == 1)) && b[y][x1].color != Player_color))
	 { 
			 if (b[y][x1].color == -1)
			 {
				 cout << "Конь выполняет ход" << "\n";
			 }
			 else { cout << "Конь наносит удар!" << "\n"; }
		 b[y][x1].color = Player_color;
		 b[y][x1].type = type_figure;
		 b[raw][column].type = n;
		 b[raw][column].color = -1;
		 return(2);
	 }
			 else { cout << "Попробуйте снова " << "\n"; return (0); }
	 case R://Проверка хода фигурой "Ладья"
		 if ((y == raw || x1 == column) && (x1 != column || y != raw) && (b[y][x1].color != Player_color) && (chek(b, y, x1, raw, column,Player_color)))
	 {
			 if (b[y][x1].color == -1)
			 {
				 cout << "Ладья выполняет ход" << "\n";
			 }
			 else { cout << "Ладья наносит удар!" << "\n"; }
	 b[y][x1].color = Player_color;
	 b[y][x1].type = type_figure;
	 b[raw][column].type = n;
	 b[raw][column].color = -1;
	 return(2);
	 }
			else { cout << "Попробуйте снова " << "\n"; return(0); }
	 case P://Проверка хода фигурой "Пешка"
		 cout << "Фигура пешка" << "\n";
		 switch(Player_color)
	    case 1:
		    if (((y - raw) == 1) && (abs(x1 - column) == 1))
	        {
				if (b[y][x1].color != Player_color)
				{
					if (y == vz_y && x1 == vz_x && b[y][x1].color == -1)
					{
						cout <<"Взятие на ходу " << "\n";
						b[y][x1].color = Player_color;
						b[y][x1].type = type_figure;
						b[y+1][x1].color = -1;
						b[y+1][x1].type = n;
						return (2);
					}
					if (b[y][x1].color == 0)
					{
						cout << "Пешка наносит удар!" << "\n";
						b[y][x1].color = Player_color;
						b[y][x1].type = type_figure;
						b[raw][column].type = n;
						b[raw][column].color = -1;
						return(2);
					}
					if (b[y][x1].color == 0&&y==8)
					{
						cout << "Выберите фигуру , на которую необходимо заменить: Q!!!!";// необходимо закончить
						return (2);
					}
					
				}
				else { cout << "Попробуйте снова " << "\n"; return(0); }
		    }
			else
			{
				if (((((y - raw) == 1) && (x1 == column)) || ((y - raw) == 2 && y == 3 && x1 == column))&&(b[y][x1].color==-1))
				{ 
					cout << "Пешка выполнила ход!" << "\n";
					if (y != 7)
					{
						b[y][x1].color = Player_color;
						b[y][x1].type = type_figure;
						b[raw][column].type = n;
						b[raw][column].color = -1;
						if ((y - raw) == 2) { cout << "ПРИСВОИЛ ИНДЕКСЫ " << "\n"; vz_y = y - 1; vz_x = x1; }
						return(2);
					}
					else
					{
						cout << "Выберите фигуру , на которую необходимо заменить: Q!!!!";// необходимо закончить
						return (2);
					}
				}
				else { cout << "Попробуйте снова " << "\n"; return(0); }
			}
		case 0:
			if (((y - raw) == -1) && (abs(x1 - column) == 1))
			{
				if (b[y][x1].color != Player_color)
				{
					if (y == vz_y && x1 == vz_x && b[y][x1].color == -1)
					{
						cout << "Взятие на ходу " << "\n";
						b[y][x1].color = Player_color;
						b[y][x1].type = type_figure;
						b[y + 1][x1].color = -1;
						b[y + 1][x1].type = n;
						return (2);
					}
					if (b[y][x1].color == 1)
					{
						cout << "Пешка наносит удар!" << "\n";
						b[y][x1].color = Player_color;
						b[y][x1].type = type_figure;
						b[raw][column].type = n;
						b[raw][column].color = -1;
						return(2);
					}
					if (b[y][x1].color == 1 && y == 1)
					{
						cout << "Выберите фигуру , на которую необходимо заменить: Q!!!!";// необходимо закончить
						return (2);
					}

				}
				else { cout << "Попробуйте снова " << "\n"; return(0); }
			}
			else
			{
				if (((((y - raw) == -1) && (x1 == column)) || ((y - raw) ==-2 && y == 4 && x1 == column)) && (b[y][x1].color == -1))
				{
					cout << "Пешка выполнила ход!" << "\n";
					if (y != 0)
					{
						b[y][x1].color = Player_color;
						b[y][x1].type = type_figure;
						b[raw][column].type = n;
						b[raw][column].color = -1;
						if ((raw-y) == 2) { cout << "ПРИСВОИЛ ИНДЕКСЫ " << "\n"; vz_y = y +1; vz_x = x1; }
						return(2);
					}
					else
					{
						cout << "Выберите фигуру , на которую необходимо заменить: Q!!!!";// необходимо закончить
						return (2);
					}
				}
				else { cout << "Попробуйте снова " << "\n"; return(0); }
			}
		default: return (0);
    }
	return (0);
}

int main()
{
	setlocale(0, "");
	int Player_color;
	bool Mat = 0; //Переменная определяющая конец игры (мат)
	int stage = 0; // Переменная определяющая этап игры  
	int type_figure;// Переменная , которая хранит значение выбранной фигуры 
	int raw, column;
	char x; int y=0;
	int vz_y = 0;
	int vz_x = 0;//Переменные определяющие осуществить прием "Взятие на проходе"
	Board b[8][8] =
	{
		{ {1,R  },{ 1,Kn},{ 1,B },{ 1,K },{ 1,Q },{ 1,B },{ 1,Kn},{ 1,R } },
		{ {1,P  },{ 1,P },{ 1,P },{ 1,P },{ 1,P },{ 1,P },{ 1,P },{ 1,P } },
		{ { -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n} },
		{ { -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n} },
		{ { -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n} },
		{ { -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n},{ -1,n} },
		{ { 0,P },{ 0,P },{ 0,P },{ 0,P },{ 0,P },{ 0,P },{ 0,P },{ 0,P } },
	    { { 0,R },{ 0,Kn},{ 0,B },{ 0,Q },{ 0,K },{ 0,B },{ 0,Kn},{ 0,R } }	
	};
	while (Mat == 0)
	{
		int flag = 0;
		switch (stage)
		{
		 case 0: Player_color = 1; cout << "Игрок 1 выберите фигуру " << "\n";
			while (flag == 0)
			{
				cin >> x >> y;
				flag = comparison(x, y, b, Player_color,type_figure,raw,column);
				if (flag == 1) { cout << "Фигура выбрана верно" << "\n";  stage = 1; }
				else { cout << "Попробуйте снова " << "\n"; }
			}
			break;
		 case 1:cout << "Игрок 1 ваш ход !"<<"\n"<<"Введите координаты " ;
			while (flag == 0)
			{
				cin >> x >> y;cout  << "\n";
				flag= course(x, y, b, type_figure, Player_color, raw, column, vz_y, vz_x);
				if (flag == 2) { stage = 2; }
			}
			break;

		 case 2: Player_color = 0; cout << "Игрок 2 выберите фигуру "<<"\n";
				while ( flag== 0)
				{
					cin >> x >> y;
					flag = comparison(x, y, b, Player_color,type_figure,raw,column);
					if (flag== 1) { cout << "Фигура выбрана верно "<<"\n"; stage = 3; }
					else { cout << "Попробуйте снова "<<"\n"; }
				}
				break;
		 case 3:cout << "Игрок 2 ваш ход !" << "\n" << "Введите координаты";
			 while (flag == 0)
			 {
				 cin >> x >> y; cout << "\n";
				 flag = course(x, y, b, type_figure, Player_color, raw, column,vz_y, vz_x);
				 if (flag == 2) { stage = 0; }
			 }
			 break;
		}
	}
    return 0;
 }

