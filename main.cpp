#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define bird 10
#define wall 11
using namespace std;

class cBird
{
private:
	int x,y;
public:
	cBird(int x, int y)
	{
		this->x = x;
		this->y = y;	
	}	
	
	void setX(int x)
	{
		this->x = x;
	}
	
	void setY(int y)
	{
		this->y = y;
	}
	
	int getX()
	{
		return x;
	}
	
	int getY()
	{
		return y;
	}
};

class cMap
{
private:
	int map[20][30];
	int s;
public:
	cMap()
	{
		s = 0;
		srand((unsigned)time(NULL));
		
		for (int i=0; i<20; i++)
		{
			for (int j=0; j<30; j++)
			{
				map[i][j] = 0;
			}
		}
	}	
	
	void changeValue(int i, int j, int m)
	{
		map[i][j] = m;
	}
	
	int getValue(int i, int j)
	{
		return map[i][j];
	}
	
	void display()
	{
		system("cls");
		for (int i=0; i<20; i++)
		{
			for (int j=0; j<30; j++)
			{
				if (map[i][j] == bird)
					cout<<"@";
				else if (map[i][j] == wall)
					cout<<"#";
				else
					cout<<" ";
			}
			cout<<endl;
		}
		cout<<"\n\n"<<s<<"m"<<endl;
	}
	
	void addS()
	{
		s++;
	}
	
	bool flush()
	{
		for (int i=0; i<20; i++)
		{
			for (int j=0; j<30; j++)
			{
				if (map[i][j] == wall)
				{
					if (j-1>=0)
					{
						if (map[i][j-1] == bird)
							return false;
						else
						{
							map[i][j-1] = map[i][j];
							map[i][j] = 0;
						}
					}
					else
						map[i][j] = 0;
				}
			}
		}
		return true;
	}
	
	void createWall(int num)
	{
		int a = rand()%(20 - num);
		for (int i=0; i<a; i++)
		{
			map[i][29] = wall;
		}
		for (int i=(a+num); i<20; i++)
		{
			map[i][29] = wall;
		}
	}
};

void Menu()
{
	system("cls");
	cout<<"\t----------------------------"<<endl;
	cout<<"\t\tFlappy Bird"<<endl;
	cout<<"\t\t>1.Start"<<endl;
	cout<<"\t\t>2.Quit"<<endl;
	cout<<"\t\t(Written By LZJmb)"<<endl;
	cout<<"\t----------------------------"<<endl;
}

bool action(cBird* b, cMap* m)
{
	int x,y;
	char ch;
	
	if (_kbhit())
	{
		ch = getch();
		y = b->getY();
		x = b->getX();
		
		switch(ch)
		{
		case 'd':
			if (y-1>=0)
			{
				if (m->getValue(y-1,x) != wall)
				{
					b->setY(y-1);
					m->changeValue(y-1,x,bird);
					m->changeValue(y,x,0);
				}
				else
					return false;
			}
			break;
		case 'a':
			if (y+1<=29)
			{
				if (m->getValue(y+1,x) != wall)
				{
					b->setY(y+1);
					m->changeValue(y+1,x,bird);
					m->changeValue(y,x,0);
				}
				else
					return false;
			}
		}
	}
	
	return true;
}

void game()
{
	bool isalive = true;
	int count = 0;
	cMap m;
	cBird b(10,10);
	m.changeValue(b.getY(),b.getX(),bird);
	
	srand((unsigned)time(NULL));
	
	while (isalive == true)
	{
		count = rand()%7+4;
		for (int i=0; i<count; i++)
		{
			m.display();
			isalive = action(&b,&m);
			isalive = m.flush();
			m.addS();
			Sleep(100);
		}
		m.createWall(count);
	}
	
	system("cls");
	cout<<"\t\tGame Over! Back to Menu in 5s ...";
	Sleep(5000);
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) 
{
	int choice;
	bool quit = false;
	
	cout<<"Before you start, you must choose the text color first"<<endl;
	cout<<"\t----------------------------"<<endl;
	cout<<"\t\t1.White\t2.Red"<<endl;
	cout<<"\t\t3.Green\t4.Blue"<<endl;
	cout<<"\t----------------------------"<<endl;
	cout<<"\n\t\tYour Choice:";
	cin>>choice;
	
	switch (choice)
	{
		case 1:
			system("color 07");
			break;
		case 2:
			system("color 04");
			break;
		case 3:
			system("color 02");
			break;
		case 4:
			system("color 01");
			break;
		default:
			system("color 07");
			break;
	}
	
	while (quit == false)
	{
		system("cls");
		Menu();
		cout<<"\n\t\tYour Choice:";
		cin>>choice;
		if (choice == 2)
			quit = true;
		else if (choice == 1)
			game();
		else 
		{
			cout<<"\n\tError! Please input again after 3s ..."<<endl;
			Sleep(3000);
		}
	}
	return 0;
}
