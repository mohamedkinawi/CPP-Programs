#include<iostream>
#include<vector>
using namespace std;

struct Node {
	vector<int> data;
	vector<Node*> links;
};
typedef Node* Nodeptr;


void output(const Nodeptr& head) {
	if (head->links.size() != 0) {
		for (int i = 0; i < head->links.size(); i++) {
			output(head->links[i]);
		}
	}
	else {
		cout << "{ ";
		for (int i = 0; i < head->data.size(); i++) {
			cout << head->data[i];
			if (i != head->data.size() - 1) {
				cout << " - ";
			}
		}
		cout << " }" << endl;
	}
}

void searchandattach(Nodeptr& head, int n) {
	if (head->links.size() == 0) {
		Nodeptr temp;
		for (int i = 0; i < n; i++) {
			temp = new Node;
			temp->data = head->data;
			temp->data.insert(temp->data.begin()+i,n);
			head->links.push_back(temp);
		}
	}
	else {
		for (int i = 0; i < head->links.size(); i++) {
			searchandattach(head->links[i], n);
		}
	}
}


void permutations(Nodeptr& head,int n) {
	if (n==1) {
		head = new Node;
		head->data.push_back(n);
	}
	else {
		permutations(head, n - 1);
		searchandattach(head, n);
	}
}

void freeheap(Nodeptr& head) {
	if (head->links.size() != 0) {
		for (int i = 0; i < head->links.size(); i++) {
			freeheap(head->links[i]);
		}
	}
	else {
		delete head;
	}
}

int factorial(int n) {
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}


int main() {
	Nodeptr head;
	for (int n = 1; n < 6; n++) {
		cout << "There are " << factorial(n) << " permutations." << endl << endl;
		permutations(head, n);
		output(head);
		cout << endl;
		freeheap(head);
	}

	return 0;
}
