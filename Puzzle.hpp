#ifndef Puzzle_HPP
# define Puzzle_HPP

#include "Library.hpp"

class Puzzle {
	private:
		std::vector<int> checking;
		std::string file;
		int size_puzzle;
		std::vector< std::vector<int> > graph;
		std::vector<int> puzzle_in_line;
		e_status status;
		int start_x;
		int start_y;

		int count_replace;

	public:
		Puzzle(std::string _file);
		~Puzzle();
		e_status parser();
		e_status checkSolution();
		e_status checkNum();

		void makeLine(std::string s, int i);
		void puzzleToLine();

		void printPole();
		void printInLine();

		e_status	getStatus();
		int			getSize();
		int			getStartX();
		int			getStartY();
		std::vector< std::vector<int> >	&getGraph();

		void	countNeedMove();

};

#endif