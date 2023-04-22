#include "Library.hpp"

Heuristics::Heuristics(int size_p) {
	genSolvePuzzle(size_p);
	type = 0;
	k = 2;
};

int Heuristics::conflicts_line(Puzzle *cur) {
	int h = 0;
	int prev_x = -1;
	int prev_y = -1;
	int size_p = cur->graph.size();
	for (int i = 1; i < size_p; i++) {
		for (int j = 1; j < size_p; j++) {
			if (set_x[i].count(cur->graph[i][j]) != 0) {
				if (prev_x != -1 && dict[prev_x] % 1000 > dict[cur->graph[i][j]] % 1000) {
					h += k;
				}
				prev_x = cur->graph[i][j];
			}
			if (set_y[i].count(cur->graph[j][i]) != 0) {
				if (prev_y != -1 && dict[prev_y] / 1000 > dict[cur->graph[j][i]] / 1000) {
					h += k;
				}
				prev_y = cur->graph[j][i];
			}
		}
		prev_x = -1;
		prev_y = -1;
	}
	h += conflicts_corner(cur);
	return(h);
}

int Heuristics::conflicts_corner(Puzzle *cur) {
	int h = 0;
	int size_p = cur->graph.size() - 1;
	int prev = size_p - 1;
	if ((cur->graph[1][2] == solve[1][2] 
	|| cur->graph[2][1] == solve[2][1])
	&& cur->graph[1][1] != solve[1][1]) {
		h += k;
	}
	if ((cur->graph[2][size_p] == solve[2][size_p] 
	|| cur->graph[1][prev] == solve[1][prev])
	 && cur->graph[1][size_p] != solve[1][size_p]) {
		h += k;
	}
	if ((cur->graph[size_p][2] == solve[size_p][2] 
	|| cur->graph[prev][1] == solve[prev][1])
	 && cur->graph[size_p][1] != solve[size_p][1]) {
		h += k;
	}
	if ((cur->graph[size_p][prev] == solve[size_p][prev]
	|| cur->graph[prev][size_p] == solve[prev][size_p])
	 && cur->graph[size_p][size_p] != solve[size_p][size_p]) {
		h += k;
	}
	return(h);
}

void Heuristics::genSolvePuzzle(int size_p) {
	int side = size_p;
	int c = 1;
	int num = 1;
	std::vector<int> tmp(size_p + 1, 0);
	solve.resize(size_p + 1, tmp);
	while (side > 2) {
		for (int j = c; j < side; j++) {
			solve[c][j] = num;
			dict[num] = c * 1000 + j;
			num++;
		}
		for (int j = c; j < side; j++) {
			solve[j][side] = num;
			dict[num] = j * 1000 + side;
			num++;
		}
		for (int j = side; j > c; j--) {
			solve[side][j] = num;
			dict[num] = side * 1000 + j;
			num++;
		}
		for (int j = side; j > c; j--) {
			solve[j][c] = num;
			dict[num] = j * 1000 + c;
			num++;
		}
		side--;
		c++;
	}
	if (size_p % 2 == 0) {
		solve[size_p / 2 + 1][size_p / 2] = 0;
		dict[0] = (size_p / 2 + 1) * 1000 + (size_p / 2);
	}
	else {
		solve[size_p / 2 + 1][size_p / 2 + 1] = 0;
		dict[0] = (size_p / 2 + 1) * 1000 + (size_p / 2 + 1);
	}
	set_x.resize(solve.size());
	set_y.resize(solve.size());
	for (size_t i = 1; i < solve.size(); ++i) {
		for (size_t j = 1; j < solve[i].size(); ++j) {
			set_x[i].insert(solve[i][j]);
			set_y[j].insert(solve[i][j]);
		}
	}
}

void Heuristics::printSolvePuzzle() {
	for (size_t i = 1; i < solve.size(); i++) {
		for (size_t j = 1; j < solve[i].size(); j++) {
			std::cout << solve[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Heuristics::getType() {
	return(type);
}

int Heuristics::getCoeff() {
	return(k);
}