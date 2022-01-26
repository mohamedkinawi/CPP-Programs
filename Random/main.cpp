// an example program to see how the "random.h" library works
// compile this file in command line "g++ -c main.cpp"
// link and produce executable "g++ random.o main.o -o executableName"

#include <iostream>
#include <ctime>
using namespace std;
#include "random.h"



int main(){
	
	//my_random::set_random_seed(1); //for debugging only, otherwise automatically random with each program run
	
	const int flips = 1000;
	int heads = 0;
	int tails = 0;
	for(int i=1;i<=flips;i++){
		if(my_random::get_random_chance(0.5)==true) heads++;
		else tails++;
	}
	cout<<"\nOut of "<<flips<<" flips:"<<endl;
	cout<<"Heads occurred "<<heads<<" times\n";
	cout<<"Tails occurred "<<tails<<" times\n\n";

	const int diceMax = 6;
	const int rolls = 1000000;
	int diceResults[diceMax] = {};
	for(int i=1;i<=rolls;i++){
		diceResults[my_random::get_random_int(1,diceMax)-1]++;
	}
	cout<<"Out of "<<rolls<<" rolls:"<<endl;
	for(int i=0;i<diceMax;i++){
		cout<<i+1<<" occurred "<<diceResults[i]<<" times"<<endl;
	}

	return 0;
}
