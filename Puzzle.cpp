# include "Library.hpp"

Puzzle::Puzzle(std::vector< std::vector<int> > _graph) {
	graph = _graph;
	prev_x = 0;
	prev_y = 0;
	g = 0;
	h = 0;
	conflict = 0;
	for (size_t i = 1; i < graph.size(); i++) {
		for (size_t j = 1; j < graph[i].size(); j++) {
			if (graph[i][j] == 0) {
				start_x = j;
				start_y = i;
			}
		}
	}
}

Puzzle::Puzzle() {
}

Puzzle::~Puzzle() {
}
