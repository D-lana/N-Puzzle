#ifndef PuzzleSolver_HPP
# define PuzzleSolver_HPP

#include "Library.hpp"

class PuzzleSolver {
	private:
		Puzzle &puzzle;
		Heuristics &h;
		std::deque<Puzzle> result;
		int count_in_time;
		int count_in_size;
		int open_size;

		int size_p;
		bool finish;

		e_bonus flag;

		std::unordered_set<Puzzle> open;
		std::map<int, std::unordered_set<Puzzle>> open_map;
		std::unordered_set<Puzzle> close;

	public:
		PuzzleSolver(Puzzle &puzzle, Heuristics &h, e_bonus flag);
		~PuzzleSolver();

		Puzzle min_f();
		
		void addNeighbour(Puzzle *puz, int x, int y);
		void getNeighbours(Puzzle *puz);
		
		void complexityInSize();
		void runAlgorithm(Puzzle cur);

		void printResult(Puzzle cur);
		void printPole(Puzzle *p);
};

#endif