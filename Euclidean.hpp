#ifndef Euclidean_HPP
# define Euclidean_HPP

#include "Library.hpp"

class Euclidean : public Heuristics {
	public:
		Euclidean(int size_p);
		~Euclidean() {};

		int h(int num, int x, int y);
		int init(Puzzle *cur);
};

#endif