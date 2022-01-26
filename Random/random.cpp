// compile this file in command line "g++ -c random.cpp"

#include <ctime>
#include <cstdlib>
#include "random.h"

namespace my_random {
	void set_random_seed(int seed){
		static bool seed_set = false;
		if(!seed_set){
			srand(seed);
			seed_set = true;
		}
	}
	void set_random_seed(){
		set_random_seed(time(0));
	}
	int get_random_int(int lower , int upper){
		set_random_seed();
		double r = static_cast<double>(rand())/RAND_MAX;				// [0,1] double
		int ans = static_cast<int>(lower + r*(static_cast<double>(upper)-lower+1));	// [lower,upper+1] int
		if(ans==static_cast<double>(upper)+1)
			return get_random_int(lower,upper);
		else return ans;
	}
	double get_random_real(double lower, double upper){
		set_random_seed();
		double r = static_cast<double>(rand())/RAND_MAX;	// [0,1] double
		double diff = r*(upper-lower);				// [0,upper-lower] double
		return lower + diff;					// [lower,upper] double
	}
	bool get_random_chance(double prob){
		set_random_seed();
		if(prob>=1) return true;
		else if(prob<=0) return false;
		else return (static_cast<double>(rand())/RAND_MAX) < prob;
		// if prob is 0.5 and static_cast<double>(rand())/RAND_MAX returned exactly 0.5 , should i roll again??
	}
}



// NOTES TO MYSELF

/*
if we want to store some values that are associated with our random generator , we can make a class to encapsulate those values, but use
a singleton pattern to allow instantiating only one object , since we can seed only one generator in the cstdlib per running program.
*/

/*
OR we could use static local variables inside the function implementations but we have to choose which function contains them because this is the only function
that has access to these variables.
*/
