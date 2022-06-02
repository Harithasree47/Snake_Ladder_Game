#include <iostream>
#include<cstdlib>
#include<vector>
using namespace std;
#define chart_size 50
struct node
{
	int data;
	// special variable indicates whether it has jumps(snakes/ladder) or not
	bool special;
	// s_l indicates it contains snake or ladder
	int s_l;
	node* ptr;
	node* next;
	node(int d)
	{
		data = d;
		special = false;
		s_l = 0;
		ptr = NULL;
		next = NULL;
	}
};
node* head=NULL;
node* end_node = NULL;
string player1, player2;
void insert_end(int value)
{
	node* temp = new node(value);
	if (head == NULL)
	{
		head = temp;
		end_node = temp;
	}
	else
	{
		end_node->next = temp;
		end_node = temp;
	}
}
// This function just creates a plain linked list
void plain_ll()
{
	int i;
	for (i = 0; i < chart_size; i++)
	{
		insert_end(i+1);
	}
}
void set_ladders(vector<int>starting, vector<int>ending)
{
	int i;
	int n = starting.size();
	node* temp1,*temp2;
	//cout << "setting ladders :\n";
	for (i = 0; i < n; i++)
	{
		temp1 = head;
		while (temp1->data != starting[i])
		{
			temp1 = temp1->next;
		}
		temp1->special = true;
		temp1->s_l = 1;
		temp2 = temp1->next;
		while (temp2->data != ending[i])
		{
			temp2 = temp2->next;
		}
		temp1->ptr = temp2;
		//cout << temp1->data << " " << temp2->data<<endl;
	}
}
void set_snakes(vector<int>starting, vector<int>ending)
{
	int i;
	int n = starting.size();
	node* temp1, * temp2;
	//cout<<"setting snakes\n";
	for (i = 0; i < n; i++)
	{
		temp1 = head;
		while (temp1->data != ending[i])
		{
			temp1 = temp1->next;
		}
		temp2 = temp1->next;
		while (temp2->data != starting[i])
		{
			temp2 = temp2->next;
		}
		temp2->ptr = temp1;
		temp2->special = true;
		temp2->s_l = 2;
		//cout << temp1->data << " " << temp2->data<<endl;
	}
}
void set_chart()
{
	plain_ll();
	int ladders;
	int snakes;
	int temp, i;
	ladders = rand() % 7;
	snakes = rand() % 7;
	vector<int>ladder_start;
	vector<int>ladder_end;
	vector<int>snake_start;
	vector<int>snake_end;
	for (i = 0; i < ladders; i++)
	{
		ladder_start.push_back(1+rand() % chart_size);
	}
	for (i = 0; i < ladders; i++)
	{
		ladder_end.push_back(ladder_start[i] + rand() % (chart_size - ladder_start[i]));
	}
	set_ladders(ladder_start, ladder_end);
	/*
	cout << "ladders :\n";
	for (i = 0; i < ladders; i++)
	{
		cout << ladder_start[i] << " " << ladder_end[i] << endl;
	}
	*/
	for (i = 0; i < snakes; i++)
	{
		snake_start.push_back(1 + rand() % chart_size);
	}
	for (i = 0; i < snakes; i++)
	{
		snake_end.push_back( rand() %  snake_start[i]);
	}
	set_snakes(snake_start, snake_end);
	/*cout << "snakes :";
	for (i = 0; i < snakes; i++)
	{
		cout << snake_start[i] << " " << snake_end[i] << endl;
	}
	*/
}
void play()
{
	node* temp1, * temp2;
	temp1 = temp2 = head;
	int i = 0,d,t;
	while (1)
	{
		if (i % 2==0)
		{
			cout <<endl<< player1 << "'s turn:";
			cout<<"\nPress t to through the die :";
			char c;
			cin >> c;
			d=rand();
			t = temp1->data + d % 7;
			if (t == chart_size)
			{
				cout << player1 << " is the winner";
				return;
			}
			if (t > chart_size)
			{
				cout << "\ntoo high to reach goal\n";
			}
			else
			{
				while (temp1->data != t)
				{
					temp1 = temp1->next;
				}
				if (temp1->special)
				{
					if (temp1->s_l == 1)
					{
						cout << "\nyou get a ladder :\n";
						temp1 = temp1->ptr;
					}
					else
					{
						cout << "\nsnake bites you :\n";
						temp1 = temp1->ptr;
					}
				}
			}
			cout << "\nyou are at position :" << temp1->data;
		}
		else
		{
			cout <<endl<< player2 << "'s turn:";
			cout<<"\nPress t to through the die :";
			char c;
			cin >> c;
			d=rand();
			t = temp2->data + d % 7;
			if (t == chart_size)
			{
				cout << player2 << " is the winner";
				return;
			}
			if (t > chart_size)
			{
				cout << "\ntoo high to reach goal\n";
			}
			else
			{
				while (temp2->data != t)
				{
					temp2 = temp2->next;
				}
				if (temp2->special)
				{
					if (temp2->s_l == 1)
					{
						cout << "you get a ladder :";
						temp2 = temp2->ptr;
					}
					else
					{
						cout << "\nsnake bites you :\n";
						temp2 = temp2->ptr;
					}
				}
			}
			cout << "\nyou are at position :" << temp2->data;
		}
		i++;
	}
}
int main()
{
	cout << "Enter player1 Name: ";
	cin >> player1;
	cout << "\nEnter player2 Name: ";
	cin >> player2;
	set_chart();
	//cout << "\nevery time enter a valid die number :\n";
	play();
	return 0;
}
