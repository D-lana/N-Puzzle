#include "Library.hpp"

CountMismatch::CountMismatch(int size_p) : Heuristics(size_p) {
	type = 3;
}

int CountMismatch::h(int num, int x, int y) {
	int x2 = dict[num] % 1000;
	int y2 = dict[num] / 1000;
	int _h = 0;
	if (x != x2) {
		_h++;
	}
	if (y != y2) {
		_h++;
	}
	return(_h);
}

int CountMismatch::init(Puzzle *cur) {
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
