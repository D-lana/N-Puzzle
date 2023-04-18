#ifndef PuzzleSolver_HPP
# define PuzzleSolver_HPP

#include "Library.hpp"

class PuzzleSolver {
	private:
		Puzzle &puzzle;
		std::vector< std::vector<int> > solve;
		std::vector< std::set<int> > set_x;
		std::vector< std::set<int> > set_y;
		std::unordered_map<int, int> dict;
		std::deque<Puzzle> result;
		int count_in_time;
		int count_in_size;

		int size_p;
		bool finish;

		std::unordered_set<Puzzle> open;
		std::unordered_set<Puzzle> close;
		std::vector<Puzzle> neighbours;
		std::vector<Puzzle> n;

	public:
		PuzzleSolver(Puzzle &puzzle);
		~PuzzleSolver();

		void genSolvePuzzle(int size_p);
		Puzzle min_f();
		int h_Manhattan(int num, int x, int y);
		void addNeighbour(Puzzle *puz, int x, int y);
		void getNeighbours(Puzzle *puz);
		int init_Manhattan(Puzzle *cur);
		void complexityInSize();
		void runAlgorithm(Puzzle cur);

		void printResult(Puzzle cur);
		void printPole(Puzzle *p);
		void printSolvePuzzle();

		int Manhattan_conflicts(Puzzle *cur);
		int Manhattan_conflicts_corner(Puzzle *cur);
};

#endif