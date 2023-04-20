#include "Library.hpp"

Manhattan::Manhattan(int size_p) : Heuristics(size_p) {}

int Manhattan::h(int num, int x, int y) {
	int x2 = dict[num] % 1000;
	int y2 = dict[num] / 1000;
	int h = std::abs(x - x2) + std::abs(y - y2);
	return(h);
}

int Manhattan::init(Puzzle *cur) {
	int num = 0;
	int h = 0;
	int size_p = cur->graph.size();
	for (int i = 1; i < size_p; i++) {
		for (int j = 1; j < size_p; j++) {
			if (cur->graph[i][j] != 0) {
				num = cur->graph[i][j];
				int x2 = dict[num] % 1000;
				int y2 = dict[num] / 1000;
				h += std::abs(j - x2) + std::abs(i - y2);
			}	
		}
	}
	return(h);
}
