/* Enter in the command line to run the program:
	> g++ -c GoL.cpp
	> g++ -c main.cpp
	> g++ GoL.o main.o -o sample
	> sample
*/


#include<iostream>
#include "GoL.h"

int main() {

	try{
		kinawi::GOL game_of_life(R"(insert_absolute_path_here\example_starting_grid.txt)");
		char ans;
		while (true) {
			std::cout<<game_of_life;
			std::cout << "Press enter for the next generation or type n to exit: ";
			std::cin.get(ans);
			if (ans == 'n')
				break;
			game_of_life.next_generation();
		}
	}
	catch(std::string e){
		std::cout<<"ERROR --> "<<e<<std::endl;
	}
	return 0;
}