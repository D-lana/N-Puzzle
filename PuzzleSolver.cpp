# include "Library.hpp"

PuzzleSolver::PuzzleSolver(Puzzle &_puzzle)
: puzzle(_puzzle), 
start(puzzle.getStartX(), puzzle.getStartY(), 0, 0) {
	start.h = h(start.x, start.y);
	std::cout << "Constructor PuzzleSolver call" << std::endl;
}

PuzzleSolver::~PuzzleSolver() {
	std::cout << "Destructor PuzzleSolver call" << std::endl;
}

void PuzzleSolver::genSolvePuzzle() {
	int size_p = puzzle.getSize();
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
	}
	for (size_t i = 1; i < solve.size(); i++) {
		for (size_t j = 1; j < solve[i].size(); j++) {
			std::cout << solve[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PuzzleSolver::initOpen(int g, int x, int y, std::deque<s_Point> &open) {
	int size_p = puzzle.getSize();
	if (x - 1 > 0) {
		open.push_back(s_Point(x - 1, y, g + 1, h(x - 1, y)));
	}
	if (y - 1 > 0) {
		open.push_back(s_Point(x, y - 1, g + 1, h(x, y - 1)));
	}
	if (x + 1 <= size_p) {
		open.push_back(s_Point(x + 1, y, g + 1, h(x + 1, y)));
	}
	if (y + 1 <= size_p) {
		open.push_back(s_Point(x, y + 1, g + 1, h(x, y + 1)));
	}
	for (size_t i = 0; i < open.size(); i++) {
		std::cout << open[i].x << "-" << open[i].y << "\n";
	}
}

void PuzzleSolver::startAlgorithmAStar() {
	std::cout << "start Algorithm!\n";
	open.push_back(start);
	//open[0].h = count_replace;
	//open[0].g = 0;
	//int cur = 0;
	//std:: cout << h(x -1, y) << "\n";
	// while (open.size() > 0) {
	// 	cur = findMinPoint();
	// 	close.push_back(open[cur]);
	// 	initOpen(g, x, y, open);
	// 	g++;
	// }
}

int	PuzzleSolver::h(int x, int y) {
	if (x < puzzle.getSize() && y < puzzle.getSize()
	&& x > 0 && y > 0) {
		std::vector< std::vector<int> >	&graph = puzzle.getGraph();
		int num = graph[y][x];
		int x2 = dict[num] % 1000;
		int y2 = dict[num] / 1000;
		std::cout << "num = " << graph[y][x] << "\n";
		std::cout << "x = " << x2 << "\n";
		std::cout << "y = " << y2 << "\n";
		
		int h = std::abs(x - x2) + std::abs(y - y2);
		std::cout << "h = " << h << "\n";
		return (h);
	}
	else error(4); ////!!!!!!!!!!!!!
	return(0);
}

int PuzzleSolver::findMinPoint() {
	int min = 100;
	int min_i = 0;
	for (size_t i = 0; i < open.size(); i++) {
		if (open[i].h + open[i].g < min) {
			min = open[i].h + open[i].g;
			min_i = i;
		}
	}
	std::cout << min << "\n";
	return (min_i);
}

int PuzzleSolver::Manhattan() {
	
	//--manhattan
	for (int i = 0; i < puzzle.getSize(); i++) {
		// if (puzzle_in_line[i] != checking[i]) {
		// 	std::cout << puzzle_in_line[i] << "-" << checking[i] << "  ";
		// }
	}
	return 0;
	//--
}


