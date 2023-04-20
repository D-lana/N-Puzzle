#ifndef Manhattan_HPP
# define Manhattan_HPP

#include "Library.hpp"

class Manhattan : public Heuristics {
	public:
		Manhattan(int size_p);
		~Manhattan() {};

		int h(int num, int x, int y);
		int init(Puzzle *cur);
};

#endif