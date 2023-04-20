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
		int conflict;
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

template<>
struct std::hash<Puzzle>
{
	std::size_t operator()(Puzzle const& s) const noexcept
	{
		long long hash = 0;
		for (size_t i = 0; i < s.graph.size(); i++) {
			for (size_t j = 0; j < s.graph[i].size(); j++) {
				hash += s.graph[i][j];
				hash = hash << 4;
			}
		}
		return hash;
	}
};

#endif