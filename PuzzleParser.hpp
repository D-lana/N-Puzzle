#ifndef PuzzleParser_HPP
# define PuzzleParser_HPP

#include "Library.hpp"

class PuzzleParser {
	private:
		std::string	file;
		e_status	status;
		int			size_puzzle;
		int			start_x;
		int			start_y;
		int			count_replace;

		std::vector< std::vector<int> >	graph;
		std::vector<int>				puzzle_in_line;

	public:
		PuzzleParser(std::string _file);
		~PuzzleParser();
		
        e_status	readFile();
		e_status	checkSolution();
		e_status	checkNum();

		void		makeLine(std::string s, int i);
		void		puzzleToLine();
		void		printPole();
		void		printInLine();
		void		countNeedMove();
		void		swapPoint(int x, int y);

		e_status	getStatus();
		int			getSize();
		int			getStartX();
		int			getStartY();
		int			getNum(int x, int y);

		std::vector< std::vector<int> >	&getGraph();
};

#endif