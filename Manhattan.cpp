#include "Library.hpp"

Manhattan::Manhattan(int size_p) : Heuristics(size_p) {
	type = 1;
	k = 2;
}

int Manhattan::h(int num, int x, int y) {
	int x2 = dict[num] % 1000;
	int y2 = dict[num] / 1000;
	int _h = std::abs(x - x2) + std::abs(y - y2);
	return(_h);
}

int Manhattan::init(Puzzle *cur) {
	int num = 0;
	int _h = 0;
	int size_p = cur->graph.size();
	for (int i = 1; i < size_p; i++) {
		for (int j = 1; j < size_p; j++) {
			if (cur->graph[i][j] != 0) {
				num = cur->graph[i][j];
				_h += h(num, j, i);
			}	
		}
	}
	return(_h);
}
