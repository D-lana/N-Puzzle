# include "Library.hpp"

PuzzleSolver::PuzzleSolver(Puzzle &_puzzle)
: puzzle(_puzzle) {
	count_in_time = 0;
	count_in_size = 0;
	//std::cout << "Constructor PuzzleSolver call" << std::endl;
}

PuzzleSolver::~PuzzleSolver() {
	//std::cout << "Destructor PuzzleSolver call" << std::endl;
}

void PuzzleSolver::printSolvePuzzle() {
	for (size_t i = 1; i < solve.size(); i++) {
		for (size_t j = 1; j < solve[i].size(); j++) {
			std::cout << solve[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PuzzleSolver::genSolvePuzzle(int size_p) {
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
}

Puzzle PuzzleSolver::min_f() {
	int min = INT_MAX;
	Puzzle min_p;
	for (auto it : open) {
		if (it.h + it.g < min) {
			min = it.h + it.g;
			min_p = it;
		}
	}
	count_in_time++;
	return(min_p);
}

int PuzzleSolver::h_Manhattan(int num, int x, int y) {
	int x2 = dict[num] % 1000;
	int y2 = dict[num] / 1000;
	int h = std::abs(x - x2) + std::abs(y - y2);
	return(h);
}

void PuzzleSolver::addNeighbour(Puzzle *puz, int x, int y) {
	int s_x = puz->start_x;
	int s_y = puz->start_y;
	Puzzle tmp = *puz;
	Puzzle puzz_min_g;
	tmp.g++;
	tmp.prev_x = s_x;
	tmp.prev_y = s_y;
	int num = 0;
	int size_p = puz->graph.size();
	if (x > 0 && y > 0 && x + 1 <= size_p && y + 1 <= size_p) {
		std::swap(tmp.graph[y][x], tmp.graph[s_y][s_x]);
		num = tmp.graph[s_y][s_x];
		tmp.h = tmp.h - h_Manhattan(num, x, y) + h_Manhattan(num, s_x, s_y);
		tmp.start_x = x;
		tmp.start_y = y;
		if (close.count(tmp) == 0) {
			if (open.count(tmp) == 0) {
				open.insert(tmp);
			}
			else {
				puzz_min_g = *open.find(tmp);
				if (puzz_min_g.g > tmp.g) {
					open.erase(tmp);
					open.insert(tmp);
				}
			}
			n.push_back(tmp);
		}
	}
}

void PuzzleSolver::getNeighbours(Puzzle *puz) {
	int x = puz->start_x;
	int y = puz->start_y;
	n.clear();
	addNeighbour(puz, x - 1, y);
	addNeighbour(puz, x, y - 1);
	addNeighbour(puz, x + 1, y);
	addNeighbour(puz, x, y + 1);
}

void PuzzleSolver::printPole(Puzzle *p) {
	for (size_t i = 1; i < p->graph.size(); i++) {
		for (size_t j = 1; j < p->graph[i].size(); j++) {
			std::cout << p->graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int PuzzleSolver::init_Manhattan(Puzzle *cur) {
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

void PuzzleSolver::printResult(Puzzle cur) {
	result.push_front(cur);
	std::string step = "Step: ";
	for (size_t i = 0; i < result.size(); i++) {
		print(BLUE, step + std::to_string(i + 1) + "\n\n");
		printPole(&result[i]);
	}
	print(BLUE, "-------- STATISTICS --------\n\n");
	print(GRAY, "Complexity in time: ");
	print(GREEN, std::to_string(count_in_time) + "\n");
	print(GRAY, "Complexity in size: ");
	print(GREEN, std::to_string(count_in_size) + "\n");
	print(GRAY, "Number of moves: ");
	print(GREEN, std::to_string(result.size()) + "\n\n");
}

void PuzzleSolver::complexityInSize() {
	int new_size = close.size() + open.size();
	if (count_in_size < new_size) {
		count_in_size = new_size;
	}
}

void PuzzleSolver::runAlgorithm(Puzzle cur) {
	cur.h = init_Manhattan(&cur);
	//std::cout << "h = " << cur.h << std::endl;
	//std::cout << "s x = " << cur.start_x << std::endl;
	//std::cout << "s y = " << cur.start_y << std::endl;
	printPole(&cur);
	open.insert(cur);
	finish = false;
	while (open.size() > 0 && finish == false) {
		cur = min_f();
		//std::cout << "h = " << cur.h << std::endl;
		if (cur.h == 0) {
			print(GREEN, "\n-------- PUZZLE SOLVED! --------\n\n");
			finish = true;
			break ;
		}
		close.insert(cur);
		open.erase(cur);
		complexityInSize();
		getNeighbours(&cur);
	}
	while (cur.prev_x != 0) {
		result.push_front(cur);
		std::swap(cur.graph[cur.prev_y][cur.prev_x], cur.graph[cur.start_y][cur.start_x]);
		if (close.find(cur) == close.end()) {
			std::cout << "ERROR!" << std::endl;
			return ;
		}
		else {
			cur = *close.find(cur);
		}
	}
	printResult(cur);
}
