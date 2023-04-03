#ifndef PuzzleSolver_HPP
# define PuzzleSolver_HPP

#include "Library.hpp"

class PuzzleSolver {
	private:
		Puzzle &puzzle;
		std::vector< std::vector<int> > solve;
		std::vector< std::vector<s_Point> > activ;
		s_Point start;
		std::map<int, int> dict;
		std::map<int, int> dictance;
		int manhattan_count;

		std::deque<s_Point> open;
		std::deque<s_Point> close;

	public:
		PuzzleSolver(Puzzle &puzzle);
		~PuzzleSolver();
        void genSolvePuzzle();
		void initOpen(int g, int x, int y);
		void startAlgorithmAStar();
		int	h(int num, int x, int y); //heuristicFunc

		int findMinPoint();
		int Manhattan();
		void initDistance();
		void updateAll(int min);
		void cycle(int count, std::vector< std::vector<int> > graph);
};

#endif