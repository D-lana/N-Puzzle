#ifndef Heuristics_HPP
# define Heuristics_HPP

#include "Library.hpp"

class Heuristics {
	public:
		Heuristics() {};
		~Heuristics() {};

        virtual int h(int num, int x, int y) = 0;
        virtual int init(Puzzle *cur) = 0;
        virtual int conflicts_line(Puzzle *cur) = 0;
        virtual int conflicts_corner(Puzzle *cur) = 0;
};

#endif