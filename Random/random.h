#ifndef RANDOM_H
#define RANDOM_H

namespace my_random {

	void set_random_seed(int seed);

	int get_random_int(int lower , int upper);

	double get_random_real(double lower, double upper);

	bool get_random_chance(double prob);
}

#endif
