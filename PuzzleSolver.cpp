# include "Library.hpp"

PuzzleSolver::PuzzleSolver(Puzzle &_puzzle, Heuristics &_h, e_bonus _flag)
: puzzle(_puzzle), h(_h), flag(_flag) {
	count_in_time = 0;
	count_in_size = 0;
	open_size = 1;
	k = 1;
}

PuzzleSolver::~PuzzleSolver() {
}

Puzzle PuzzleSolver::min_f() {
	while (open_map.begin()->second.size() == 0) {
		open_map.erase(open_map.begin()->first);
		if (open_map.size() == 0) {
			std::cout << "ERROR!" << std::endl;
			exit(-1);
		}
	}
	Puzzle min_p = *open_map.begin()->second.begin();
	count_in_time++;
	return(min_p);
}

void PuzzleSolver::addNeighbour(Puzzle *puz, int x, int y) {
	int s_x = puz->start_x;
	int s_y = puz->start_y;
	Puzzle tmp = *puz;
	Puzzle puzz_min_g;
	if (flag != GREEDY_SEARCH) {
		tmp.g++;
	}
	tmp.prev_x = s_x;
	tmp.prev_y = s_y;
	int num = 0;
	int size_p = puz->graph.size();
	int h_map = 0;
	if (x > 0 && y > 0 && x + 1 <= size_p && y + 1 <= size_p) {
		std::swap(tmp.graph[y][x], tmp.graph[s_y][s_x]);
		num = tmp.graph[s_y][s_x];
		tmp.h = tmp.h - h.h(num, x, y) + h.h(num, s_x, s_y);
		tmp.conflict = h.conflicts_line(&tmp);
		tmp.start_x = x;
		tmp.start_y = y;
		h_map = tmp.h + (tmp.g * k) + tmp.conflict;
		if (flag == UNIFORM_COST_SEARCH) {
			h_map = (tmp.g * k);
		}
		if (close.count(tmp) == 0) {
			if (open_map[h_map].count(tmp) == 0) {
				open_map[h_map].insert(tmp);
			}
			else {
				puzz_min_g = *open_map[h_map].find(tmp);
				if (puzz_min_g.g > tmp.g) {
					open_map[h_map].erase(tmp);
					open_map[h_map].insert(tmp);
				}
			}
			open_size++;
		}
	}
}

void PuzzleSolver::getNeighbours(Puzzle *puz) {
	int x = puz->start_x;
	int y = puz->start_y;
	addNeighbour(puz, x - 1, y);
	addNeighbour(puz, x, y - 1);
	addNeighbour(puz, x + 1, y);
	addNeighbour(puz, x, y + 1);
}

void PuzzleSolver::runAlgorithm(Puzzle cur) {
	k = h.getCoeff() / 2;
	cur.h = h.init(&cur);
	cur.conflict = h.conflicts_line(&cur);
	printPole(&cur);
	open.insert(cur);
	int h_map = cur.h + (cur.g * k) + cur.conflict;
	if (flag == UNIFORM_COST_SEARCH) {
		h_map = cur.g;
	}
	open_map[h_map] = open;
	finish = false;
	while (finish == false) {
		cur = min_f();
		h_map = cur.h + (cur.g * k) + cur.conflict;
		if (flag == UNIFORM_COST_SEARCH) {
			h_map = (cur.g * k);
		}
		if (cur.h == 0) {
			print(GREEN, "-------- PUZZLE SOLVED! --------\n\n");
			finish = true;
			break ;
		}
		close.insert(cur);
		open_map[h_map].erase(cur);
		complexityInSize();
		getNeighbours(&cur);
	}
	while (cur.prev_x != 0) {
		result.push_front(cur);
		std::swap(cur.graph[cur.prev_y][cur.prev_x], cur.graph[cur.start_y][cur.start_x]);
		if (close.find(cur) == close.end()) {
			std::cout << "ERROR!" << std::endl;
			exit(-1);
		}
		else {
			cur = *close.find(cur);
		}
	}
	printResult(cur);
}

void PuzzleSolver::printResult(Puzzle cur) {
	result.push_front(cur);
	std::string step = "Step: ";
	for (size_t i = 0; i < result.size(); i++) {
		print(BLUE, step + std::to_string(i + 1) + "\n");
		printPole(&result[i]);
	}
	print(BLUE, "-------- STATISTICS --------\n\n");
	print(GRAY, "Complexity in time: ");
	print(GREEN, std::to_string(count_in_time) + "\n");
	print(GRAY, "Complexity in size: ");
	print(GREEN, std::to_string(count_in_size) + "\n");
	print(GRAY, "Number of moves: ");
	print(GREEN, std::to_string(result.size()) + "\n");
}

void PuzzleSolver::complexityInSize() {
	open_size--;
	int new_size = close.size() + open_size;
	if (count_in_size < new_size) {
		count_in_size = new_size;
	}
}

void PuzzleSolver::printPole(Puzzle *p) {
	std::cout << std::endl;
	for (size_t i = 1; i < p->graph.size(); i++) {
		for (size_t j = 1; j < p->graph[i].size(); j++) {
			std::cout << p->graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
