#ifndef CountMismatch_HPP
# define CountMismatch_HPP

#include "Library.hpp"

class CountMismatch : public Heuristics {
	public:
		CountMismatch(int size_p);
		~CountMismatch() {};

		int h(int num, int x, int y);
		int init(Puzzle *cur);
};

#endif