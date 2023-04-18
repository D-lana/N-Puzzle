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
		std::map<int, std::unordered_set<Puzzle>> open_map;
		std::unordered_set<Puzzle> close;
		std::map<int, std::unordered_set<Puzzle>> close_map;
		std::vector<Puzzle> neighbours;
		std::vector<Puzzle> n;

	public:
		PuzzleSolver(Puzzle &puzzle);
		~PuzzleSolver();

		void genSolvePuzzle(int size_p);
		Puzzle min_f();
		
		void addNeighbour(Puzzle *puz, int x, int y);
		void getNeighbours(Puzzle *puz);
		
		void complexityInSize();
		void runAlgorithm(Puzzle cur);

		void printResult(Puzzle cur);
		void printPole(Puzzle *p);
		void printSolvePuzzle();

		int init_Manhattan(Puzzle *cur);
		int h_Manhattan(int num, int x, int y);
		int Manhattan_conflicts(Puzzle *cur);
		int Manhattan_conflicts_corner(Puzzle *cur);

		int h_Euclidean(int num, int x, int y);
		int Euclidean_metric(Puzzle *cur);
};

#endif