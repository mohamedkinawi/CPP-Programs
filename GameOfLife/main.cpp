#include<iostream>
#include<fstream>
using namespace std;

// grid dimension is 40 by 40 cells
const int square = 40; 

// function declarations/prototypes
void display(char a[][square][2], int layertodisplay);
void generation(char a[][square][2], int testlayer, int copytolayer);
char test(const char a[][square][2], int totesty, int totestr, int totestlayer, char element);



int main() {

	// 3-d array. think of it as 2 square 2-d arrays stacked above each other.
	char world[square][square][2];
	
	ifstream start;
	start.open(R"(D:\folder1\folder2\starting_configuration.txt)");
	if (start.fail()) {
		cout << "failed to open the starting configuration file";
		exit(1);
	}
	for(int y=0;y< square;y++){
		for (int r = 0; r < square; r++) {
			start >> world[y][r][1];
		}
	}
	start.close();

	int count = 1;
	char ans;
	while (true) {
		display(world, count%2);
		cout << "Press enter for the next generation or type n to exit: ";
		cin.get(ans);
		if (ans == 'n')
			break;
		count++;
		generation(world,(count-1)%2 ,count%2);
	}
	cout <<endl<< "You have displayed " << count << " generations." << endl<<endl;

	return 0;
}

void display(char a[][square][2], int layertodisplay) {
	for (int y = 1; y < square - 1; y++) {
		for (int r = 1; r < square - 1; r++) {
			if (a[y][r][layertodisplay] == '0')
				cout << ' ';
			else cout << "+";
			cout << "  ";
		}
		cout << endl;
	}
}

void generation(char a[][square][2], int testlayer, int copytolayer) {
	for (int y = 1; y < square - 1; y++)
		for (int r = 1; r < square - 1; r++)
			a[y][r][copytolayer] = test(a, y, r, testlayer, a[y][r][testlayer]);
}

char test(const char a[][square][2], int totesty, int totestr, int totestlayer, char element) {
	int count = 0;
	for (int g = -1; g <= 1; g++)
		for (int u = -1; u <= 1; u++) {
			if (a[totesty + g][totestr + u][totestlayer] == '+')
				count++;
			if (g == 0 and u == -1)
				u++;
		}
	if (element == '0') {
		if (count == 3)
			return '+';
		else
			return '0';
	}
	if (element == '+') {
		if (count == 2 or count == 3)
			return '+';
		else
			return '0';
	}

}

/*
Compile in command line g++ main.cpp main.exe
Run main.exe
*/
