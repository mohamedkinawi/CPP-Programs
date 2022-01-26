#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* link;
};
typedef Node* Nodeptr;

void inserttop(Nodeptr& head, int data) {
	Nodeptr temp = new Node;
	temp->data = data;
	temp->link = head;
	head = temp;
}
void deletetop(Nodeptr& head) {
	Nodeptr temp = head;
	head= head->link;
	delete temp;
}

int other(int n, int m) {
	switch (n + m) {
	case 3:
		return 3;
		break;
	case 5:
		return 1;
		break;
	case 4:
		return 2;
		break;
	default:
		cout << "undefined input" << endl;
	}
}

void form(int n, Nodeptr arr[]) {
	for (int i = 0; i < 4; i++)
		arr[i] = nullptr;
	Nodeptr temp;
	for (int i = n; i >= 1; i--) {
		temp = new Node;
		temp->data = i;
		temp->link = arr[1];
		arr[1] = temp;
	}
}

void print(int n, Nodeptr arr[], int from, int to) {
	if (n == 1) {
		inserttop(arr[to], n);
		deletetop(arr[from]);
		cout << "Move disk from post " << from << " to post " << to << endl;
	}
	else {
		print(n - 1, arr, from, other(from, to));
		cout << "Move disk from post " << from << " to post " << to << endl;
		inserttop(arr[to], n);
		deletetop(arr[from]);
		print(n - 1, arr, other(from, to), to);
	}
}

void play(int n) {
	Nodeptr arr[4];
	form(n, arr);
	print(n, arr, 1, 2);
}

int main() {
	cout <<endl<< "----------------------------------------------------" << endl;
	cout << "\t\tTOWERS OF HANOI" << endl << "----------------------------------------------------" << endl << endl;
	int n = 64;
	double number_of_actions = 0;
	for (int i = 0; i < n; i++)
		number_of_actions += pow(2, i);
	cout << "The total number of actions required to move " << n << " disks from post 1 to post 2 is " << number_of_actions << endl;
	cout << "Indeed, time will end if this is to be done..." << endl << endl << endl << endl << endl << endl << endl << endl;
	//play(n);
	return 0;
}