#ifndef Heuristics_HPP
# define Heuristics_HPP

#include "Library.hpp"

class Heuristics {
	protected:
		std::unordered_map<int, int> dict;
		std::vector< std::set<int> > set_x;
		std::vector< std::set<int> > set_y;
		std::vector< std::vector<int> > solve;
		int type;
	public:
		Heuristics(int size_p);
		virtual ~Heuristics() {};

		virtual int h(int num, int x, int y) = 0;
		virtual int init(Puzzle *cur) = 0;

		int conflicts_line(Puzzle *cur);
		int conflicts_corner(Puzzle *cur);
		void genSolvePuzzle(int size_p);
		void printSolvePuzzle();
		int getType();
};

#endif