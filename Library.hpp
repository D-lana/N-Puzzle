#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
# include <sstream>
# include <fstream>
# include <algorithm>
# include <cmath>
# include <set>
# include <map>
#include <stdlib.h> 
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>

#define PATH_TO_FILE "input.txt"

enum e_color
{
	RED = 91,
	GREEN = 92,
	YELLOW = 93,
	DARK_BLUE = 94,
	PINK = 95,
	BLUE = 96,
	GRAY = 30
};

enum e_status
{
	READY,
	SUCCESS,
	FAIL
};

inline void error(e_color color, int err)
{
	std::cerr << "\x1b[1;" << color << "m";
	if (err == 1) {
		std::cerr << "Error! Input data is impossible!" << "\x1b[0m" << std::endl;
	}
	else if (err == 2) {
		std::cerr << "Error! Incorrect numbers!" << "\x1b[0m" << std::endl;
	}
	else if (err == 3) {
		std::cerr << "Error! Puzzle is not solvable!" << "\x1b[0m" << std::endl;
	}
	else if (err == 4) {
		std::cerr << "Error! Heurictic error!" << "\x1b[0m" << std::endl;
	}
}

inline int toNumber(std::string s)
{
	int value = 0;
	std::stringstream ss(s);
	ss >> value;
	return value;
}

inline void print(e_color color, std::string str) 
{
	std::cout << "\x1b[1;" << color << "m";
	std::cout << str << "\x1b[0m";
}

# include "Puzzle.hpp"
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
# include "PuzzleSolver.hpp"
# include "PuzzleParser.hpp"
