# include "Library.hpp"

PuzzleParser::PuzzleParser(std::string _file) {
	this->file = _file;
	status = READY;
	count_replace = 0;
	//std::cout << "Constructor PuzzleParser call" << std::endl;
}

PuzzleParser::~PuzzleParser() {
	//std::cout << "Destructor PuzzleParser call" << std::endl;
}

void PuzzleParser::makeLine(std::string s, int i) {
	int value = 0;
	std::stringstream ss(s);
	if (i > size_puzzle) status = FAIL;
	graph[i].push_back(0);
	for (int j = 1; j < size_puzzle + 1; j++) {
		ss >> value;
		graph[i].push_back(value);
		if (value == 0) {
			start_x = i;
			start_y = j;
		}
	}
}

e_status PuzzleParser::readFile() {
	std::ifstream cin(file.c_str());
	std::string line;
	int i = 0;
	size_puzzle = 0;
	while (getline(cin, line) && status != FAIL) {
		if (line[0] != '#') {
			if (i == 0) {
				size_puzzle = toNumber(line);
				if (size_puzzle == 0 || size_puzzle > 10) status = FAIL;
				graph.resize(size_puzzle + 1);
			}
			else {
				makeLine(line, i);
			}
			i++;
		}
	}
	if (i < size_puzzle + 1) status = FAIL;
	if (status == FAIL) {
		error(RED, 1);
	}
	return (status);
}

void PuzzleParser::printPole() {
	for (size_t i = 1; i < graph.size(); i++) {
		for (size_t j = 1; j < graph[i].size(); j++) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PuzzleParser::printInLine() {
	for (size_t i = 0; i < puzzle_in_line.size(); i++) {
		std::cout << puzzle_in_line[i] << " ";
	}
	std::cout << "\n";
}

void PuzzleParser::puzzleToLine() {
	int side = size_puzzle;
	int c = 1;
	while (side > 2) {
		for (int j = c; j < side; j++) {
			puzzle_in_line.push_back(graph[c][j]);
		}
		for (int j = c; j < side; j++) {
			puzzle_in_line.push_back(graph[j][side]);
		}
		for (int j = side; j > c; j--) {
			puzzle_in_line.push_back(graph[side][j]);
		}
		for (int j = side; j > c; j--) {
			puzzle_in_line.push_back(graph[j][c]);
		}
		side--;
		c++;
	}
	if (size_puzzle % 2 != 0) {
		puzzle_in_line.push_back(graph[size_puzzle / 2 + 1][size_puzzle / 2 + 1]);
		// проверить!!! возможно нужно graph[size_puzzle / 2 + 1][size_puzzle / 2]
	}
}

e_status PuzzleParser::checkNum() {
	std::set<int> checking;
	int check_size = std::pow(size_puzzle, 2);
	for (int i = 0; i < check_size; i++) {
		checking.insert(i);
	}
	for (size_t i = 1; i < graph.size(); i++) {
		for (size_t j = 1; j < graph[i].size(); j++) {
			checking.erase(graph[i][j]);
		}
	}
	if (checking.size() != 0) {
		error(RED, 2);
		return (FAIL);
	} 
	return (SUCCESS);
}

e_status PuzzleParser::checkSolution() {
	puzzleToLine();
	int	count_inversion = 0;
	size_t size_p = puzzle_in_line.size();
	for (size_t i = 0; i < size_p; i++) {
		for (size_t j = i + 1; j < size_p; j++) {
			if (puzzle_in_line[i] > puzzle_in_line[j]) {
				count_inversion++;
			}
		}
	}
	if (count_inversion == 0 
	&& puzzle_in_line[std::pow(size_puzzle, 2) - 1] == 0) {
		print(GREEN, "\n-------- Puzzle is already solved! Yahoo! --------\n\n");
		status = SUCCESS;
	}
	else if (size_puzzle % 2 != 0 && count_inversion % 2 != 0) {
		print(RED, "\n-------- Puzzle is unsolvable! --------\n\n");
		status = FAIL;
	}
	else if (size_puzzle % 2 == 0 && (start_x + count_inversion) % 2 == 0) {
		print(RED, "\n-------- Puzzle is unsolvable! --------\n\n");
		status = FAIL;
		/*
		# This puzzle is unsolvable
		4
		7  3  6  9 
		1 11 14  2 
		8  0  5 10 
		12 15  4 13 
		*/
	}
	std::cout << "start line: " << start_x;
	std::cout << " count_inversion: " << count_inversion << "\n";
	if (status == READY) {
		countNeedMove();
	}
	return (status);
}

void	PuzzleParser::countNeedMove() {
	int check_size = std::pow(size_puzzle, 2);
	for (int i = 1; i < check_size; i++) {
		checking.push_back(i);
	}
	checking.push_back(0);
	for (size_t i = 0; i < puzzle_in_line.size(); i++) {
		if (puzzle_in_line[i] != checking[i]) {
			count_replace++;
		}
	}
}

void PuzzleParser::swapPoint(int x, int y) {
	std::swap(graph[y][x], graph[start_y][start_x]);
	start_y = y;
	start_x = x;
}

e_status PuzzleParser::getStatus() {
	return(status);
}

int PuzzleParser::getSize() {
	return(size_puzzle);
}

int PuzzleParser::getStartX() {
	return(start_x);
}
int PuzzleParser::getStartY() {
	return(start_y);
}
int PuzzleParser::getNum(int x, int y) {
	return(graph[y][x]);
}
std::vector< std::vector<int> >	&PuzzleParser::getGraph() {
	return(graph);
}