#include<iostream>
#include<cmath>
#include<stack>
using namespace std;

int minimum_number_of_moves(int number_of_disks);
void play(int number_of_disks, int from, int to);
void fill_starting_post(int number_of_disks, stack<int> posts[], int starting_post);
void move(int number_of_disks, stack<int> posts[], int from, int to);
void move_one_disk(stack<int> posts[], int from, int to);
int get_third_post(int p1, int p2);

int main()
{
	while(1)
	{
		int number_of_disks, from , to;
		cout<<"\n\nEnter number of disks, 0 to end: ";
		cin >> number_of_disks;
		if(!number_of_disks)
			return 0;
		cout << "--> The minimum number of moves required is " << minimum_number_of_moves(number_of_disks) << endl;
		cout<<"There are 3 posts, numbered 1,2 and 3.\n";
		cout<<"Enter starting post (the post number that you want to move the disks from): ";
		cin>>from;
		cout<<"Enter ending post (the post number that you want to move the disks to): ";
		cin>>to;
		cout << "--> The smallest disk is disk (#1) which starts at the top of post number " << from << endl;
		cout << "--> The largest disk is disk (#" << number_of_disks << ") which starts at the bottom of post number " << from << endl << endl << endl;
		play(number_of_disks,from,to);
	}
}

int minimum_number_of_moves(int number_of_disks)
{
	int moves = 0;
	for (int i = 0; i < number_of_disks; i++)
		moves += pow(2, i);
	return moves;
}

void play(int number_of_disks,int from, int to)
{
	stack<int> posts[3];
	fill_starting_post(number_of_disks, posts, from-1);
	move(number_of_disks, posts, from-1, to-1);
}

void fill_starting_post(int number_of_disks, stack<int> posts[], int starting_post)
{
	for (int disk_number = number_of_disks; disk_number >= 1; disk_number--) {
		posts[starting_post].push(disk_number);
	}
}

void move(int number_of_disks, stack<int> posts[], int from, int to) {
	if (number_of_disks == 1) {
		move_one_disk(posts,from,to);
	}
	else {
		int third_post = get_third_post(from,to);
		move(number_of_disks - 1, posts, from, third_post);
		move_one_disk(posts,from,to);
		move(number_of_disks - 1, posts, third_post, to);
	}
}

void move_one_disk(stack<int> posts[], int from, int to)
{
	int disk_to_move = posts[from].top();
	posts[to].push(disk_to_move);
	posts[from].pop();
	cout << "Move disk (#"<<disk_to_move<<") from post " << from+1 << " to post " << to+1 << endl;
}

int get_third_post(int p1, int p2)
{
	switch (p1 + p2)
	{
		case 1:
			return 2;
		case 2:
			return 1;
		case 3:
			return 0;
	}
}
