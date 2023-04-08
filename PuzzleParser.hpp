#ifndef PuzzleParser_HPP
# define PuzzleParser_HPP

#include "Library.hpp"

class PuzzleParser {
	private:
		std::vector<int> checking; //??
		std::string file;
		int size_puzzle;
		std::vector< std::vector<int> > graph;
		std::vector<int> puzzle_in_line; //??
		e_status status;
		int start_x;
		int start_y;

		int count_replace;

	public:
		PuzzleParser(std::string _file);
		~PuzzleParser();
        e_status readFile();
        void makeLine(std::string s, int i);
		e_status checkSolution();
		e_status checkNum();

		void puzzleToLine();

		void printPole();
		void printInLine();

		e_status	getStatus();
		int			getSize();
		int			getStartX();
		int			getStartY();
		int			getNum(int x, int y);
		std::vector< std::vector<int> >	&getGraph();

		void	countNeedMove();
		void swapPoint(int x, int y);
};

#endif