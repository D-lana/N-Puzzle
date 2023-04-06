# include "Library.hpp"

PuzzleSolver::PuzzleSolver(Puzzle &_puzzle)
: puzzle(_puzzle), start(puzzle.getStartY(), puzzle.getStartX(), 0, 0) {
	int size_p = puzzle.getSize();
	if (size_p % 2 == 0) {
		dict[0] = (size_p / 2 + 1) * 1000 + (size_p / 2);
	}
	else 
		dict[0] = (size_p / 2 + 1) * 1000 + (size_p / 2 + 1);
	start.h = h(0, start.x, start.y);
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
	//----print
	// for (size_t i = 1; i < solve.size(); i++) {
	// 	for (size_t j = 1; j < solve[i].size(); j++) {
	// 		std::cout << solve[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;
}

void PuzzleSolver::initDistance() {
	int num = 0;
	manhattan_count = 0;
	std::vector< std::vector<int> >	&graph = puzzle.getGraph();
	print(YELLOW, "> heuristic to all!\n");
	for (size_t y = 1; y < graph.size(); y++) {
		for (size_t x = 1; x < graph.size(); x++) {
			num = graph[y][x];
			dictance[num] = h(num, x, y);
			manhattan_count += dictance[num];
			std::cout << "num = "<< num << ", h = " << dictance[num] << "\n";
		}
		std::cout << "\n";
	}
	manhattan_count -= dictance[0];
	std::cout << "manhattan_count = " << manhattan_count << "\n";
}

void PuzzleSolver::initOpen(int g, int x, int y) {
	int size_p = puzzle.getSize();
	std::vector< std::vector<int> >	&graph = puzzle.getGraph();
	int num = 0;
	int dist = 0;
	if (x - 1 > 0) {
		num = graph[y][x - 1];
		dist = manhattan_count - dictance[num] + h(num, x, y);
		open.push_back(s_Point(x - 1, y, g + 1, dist));
	}
	if (y - 1 > 0) {
		num = graph[y - 1][x];
		dist = manhattan_count - dictance[num] + h(num, x, y);
		open.push_back(s_Point(x, y - 1, g + 1, dist));
	}
	if (x + 1 <= size_p) {
		num = graph[y][x + 1];
		dist = manhattan_count - dictance[num] + h(num, x, y);
		open.push_back(s_Point(x + 1, y, g + 1, dist));
	}
	if (y + 1 <= size_p) {
		num = graph[y + 1][x];
		dist = manhattan_count - dictance[num] + h(num, x, y);
		open.push_back(s_Point(x, y + 1, g + 1, h(num, x, y)));
	}
	print(RED, "> heuristicFunc!\n");
	for (size_t i = 0; i < open.size(); i++) {
		std::cout << "xy = "<< open[i].x << "-" << open[i].y;
		std::cout << " h = " << open[i].h << "\n";
	}
}

void PuzzleSolver::updateAll(int min) {
	int num = puzzle.getNum(open[min].x, open[min].y);
	dict[num] = start.y * 1000 + start.x;
	start.y = puzzle.getStartY();
	start.x = puzzle.getStartX();
}

void PuzzleSolver::cycle(int count, std::vector< std::vector<int> > graph) {
	if (count == 0) {
		return;
	}
	else {
		initOpen(0, start.x, start.y);
		int min = findMinPoint();
		std::swap(graph[start.y][start.x], graph[open[min].y][open[min].x]);
		cycle(count, graph);
	}
}

void PuzzleSolver::startAlgorithmAStar() {
	std::vector< std::vector<int> >	graph = puzzle.getGraph();
	cycle(manhattan_count, graph);
	///
	std::cout << "start Algorithm!\n";
	//open.push_back(start);
	std::cout << "start xy = "<< start.x << "-" << start.y << "\n";
	initOpen(0, start.x, start.y);
	int min = findMinPoint();
	updateAll(min);
	puzzle.swapPoint(open[min].x, open[min].y);
	open.clear();
	initOpen(0, start.x, start.y);
	min = findMinPoint();
	updateAll(min);
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

int	PuzzleSolver::h(int num, int x, int y) {
	if (x < puzzle.getSize() + 1 && y < puzzle.getSize() + 1
	&& x > 0 && y > 0) {
		// std::vector< std::vector<int> >	&graph = puzzle.getGraph();
		// int num = graph[y][x];
		if (dict.find(num) == dict.end()) {
			//std::cout << "AAAAAAA\n";
		}
		int x2 = dict[num] % 1000;
		int y2 = dict[num] / 1000;
		int h = std::abs(x - x2) + std::abs(y - y2);
		//std::cout << "h = " << h << "\n";
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
	print(RED, "> findMinPoint: ");
	manhattan_count = min;
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

