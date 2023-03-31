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

#define PATH_TO_FILE "input.txt"

// template<typename T>
// std::string toString(const T& value)
// {
// 	std::ostringstream oss;
// 	oss << value;
// 	return oss.str();
// }

inline void error(int err)
{
	if (err == 1) {
		std::cerr << "Error! Input data is impossible!" << std::endl;
		exit(-1);
	}
	if (err == 2) {
		std::cerr << "Error! Incorrect numbers!" << std::endl;
		exit(-1);
	}
	if (err == 3) {
		std::cerr << "Error! Puzzle is not solvable!" << std::endl;
		exit(-1);
	}
	if (err == 4) {
		std::cerr << "Error! Heurictic error!" << std::endl;
		exit(-1);
	}
}

inline int toNumber(std::string s)
{
	int value = 0;
	std::stringstream ss(s);
	ss >> value;
	return value;
}

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

inline void print(e_color color, std::string str) 
{
	std::cout << "\x1b[1;" << color << "m";
	std::cout << str << "\x1b[0m";
}

// inline int heuristicFunc(int g, int x, int y) 
// {
// 	int h = 0;
// 	int f = g + h;
// 	return (f);
// }

struct s_Point {
	int x;
	int y;
	int cost;
	int g;
	int h;
	s_Point(int x, int y, int g, int h) : x(x), y(y), g(g), h(h) {
	}
};

enum e_status
{
	READY,
	SUCCESS,
	FAIL
};

# include "Puzzle.hpp"
# include "PuzzleSolver.hpp"
