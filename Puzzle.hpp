#ifndef Puzzle_HPP
# define Puzzle_HPP

#include "Library.hpp"

class Puzzle {
	public:
		std::vector<std::vector<int>> graph;
		int g;
		int h;
		int start_x;
		int start_y;
		int prev_x;
		int prev_y;
		bool operator==(const Puzzle &other) const
		{
			for (size_t i = 0; i < graph.size(); i++) {
				for (size_t j = 0; j < graph[i].size(); j++) {
					if (graph[i][j] != other.graph[i][j])
						return(false);
				}
			}
			return(true);
		}
		Puzzle(std::vector< std::vector<int> > _graph);
		Puzzle();
		~Puzzle();
};

#endif