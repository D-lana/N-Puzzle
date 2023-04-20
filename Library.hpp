#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <stdlib.h> 

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

enum e_bonus
{
	UNIFORM_COST_SEARCH,
	GREEDY_SEARCH,
	NO_BONUS
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

inline void printHelp() {
	print(YELLOW, "Please, enter the following arguments:\n");
	print(YELLOW, "necessary arg:\n");
	print(GRAY, "path to the file (input.txt)\n");
	print(YELLOW, "options:\n");
	print(GRAY, "-h=m Manhattan\n-h=e Euclidean\n-h=c Count Mismatch\n");
	print(GRAY, "-g=0 Greedy search\n-h=0 Uniform cost search\n");
	print(GRAY, "Example no bonus: ./n_puzzle input.txt -h=m\n");
	print(GRAY, "Example bonus: ./n_puzzle input.txt -h=m -g=0\n");
}

# include "Puzzle.hpp"
# include "Heuristics.hpp"
# include "Manhattan.hpp"
# include "Euclidean.hpp"
# include "CountMismatch.hpp"
# include "PuzzleSolver.hpp"
# include "PuzzleParser.hpp"
