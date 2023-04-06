#include "Library.hpp"
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <vector>

struct Puzz {
	std::vector<std::vector<int>> graph;
	int g;
	int h;
	int start_x;
	int start_y;
		bool operator==(const Puzz &other) const
		{
			for (short i = 0; i < graph.size(); i++) {
				for (short j = 0; j < graph[i].size(); j++) {
					if (graph[i][j] != other.graph[i][j])
						return(false);
				}
			}
			return(true);
		}
};

std::vector< std::vector<int> > solve;
std::unordered_map<int, int> dict;

void genSolvePuzzle(int size_p) {
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
	for (size_t i = 1; i < solve.size(); i++) {
		for (size_t j = 1; j < solve[i].size(); j++) {
			std::cout << solve[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::ifstream cin("input.txt");
int size_p;

bool finish;

int **table;

int **initMassiv(int n, int m) {
	int **table = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		table[i] = (int*)malloc(m * sizeof(int));
	}
	return (table);
}

void freeMassiv(int n, int **table) {
	for (int i = 0; i < n; i++) {
		free(table[i]);
	}
	free(table);
}

template<>
struct std::hash<Puzz>
{
	std::size_t operator()(Puzz const& s) const noexcept
	{
		long long hash = 0;
		for (size_t i = 0; i < s.graph.size(); i++) {
			for (size_t j = 0; j < s.graph[i].size(); j++) {
				hash += s.graph[i][j];
				hash = hash * 10;
			}
		}
		return hash;
	}
};

std::unordered_set<Puzz> open;
std::unordered_set<Puzz> close;
std::vector<Puzz> neighbours;
std::vector<Puzz> n;

Puzz min_f() {
	int min = INT_MAX;
	Puzz min_p;
	for (auto it : open) {
		if (it.h + it.g < min) {
			min = it.h + it.g;
			min_p = it;
		}
	}
	return(min_p);
}

void removeInOpen(Puzz *puz) {
	open.erase(*puz);
}

void addInClose(Puzz *puz) {
	open.insert(*puz);
}

int h_Manhattan(int num, int x, int y) {
	int x2 = dict[num] % 1000;
	int y2 = dict[num] / 1000;
	int h = std::abs(x - x2) + std::abs(y - y2);
	return(h);
}

void addNeighbour(Puzz *puz, int x, int y) {
	int s_x = puz->start_x;
	int s_y = puz->start_y;
	Puzz tmp = *puz;
	tmp.g++;
	int num = 0;
	if (x > 0 && y > 0 && x + 1 <= puz->graph.size() && y + 1 <= puz->graph.size()) {
		std::cout << "addNeighbour > " << x << " " << y << "\n";
		std::swap(tmp.graph[y][x], tmp.graph[s_y][s_x]);
		num = tmp.graph[s_y][s_x];
		tmp.h = tmp.h - h_Manhattan(num, x, y) + h_Manhattan(num, s_x, s_y);
		std::cout << "for " << num << "= - " << h_Manhattan(num, x, y);
		std::cout << " + " << h_Manhattan(num, s_x, s_y);
		std::cout << ", h = " << tmp.h << std::endl;
		tmp.start_x = x;
		tmp.start_y = y;
		if (close.count(tmp) == 0) {
			if (open.count(tmp) == 0) {
				open.insert(tmp);
			}
			n.push_back(tmp);
		}
	}
}

void getNeighbours(Puzz *puz) {
	int x = puz->start_x;
	int y = puz->start_y;
	n.clear();
	addNeighbour(puz, x - 1, y);
	addNeighbour(puz, x, y - 1);
	addNeighbour(puz, x + 1, y);
	addNeighbour(puz, x, y + 1);
}

void printPole(Puzz *p) {
	for (size_t i = 1; i < p->graph.size(); i++) {
		for (size_t j = 1; j < p->graph[i].size(); j++) {
			std::cout << p->graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int init_Manhattan(Puzz *cur) {
	int num = 0;
	int h = 0;
	for (int i = 1; i < cur->graph.size(); i++) {
		for (int j = 1; j < cur->graph[i].size(); j++) {
			if (cur->graph[i][j] != 0) {
				num = cur->graph[i][j];
				int x2 = dict[num] % 1000;
				int y2 = dict[num] / 1000;
				h += std::abs(j - x2) + std::abs(i - y2);
				//std::cout << "h += " << h << std::endl;
			}	
		}
	}
	return(h);
}

int main() { 
	cin >> size_p;
	int m = 0;
	Puzz cur;
	cur.graph.resize(size_p + 1);
	for (int i = 1; i < size_p + 1; i++) {
		cur.graph[i].push_back(0);
		for (int j = 1; j < size_p + 1; j++) {
			cin >> m;
			cur.graph[i].push_back(m);
			if (m == 0) {
				cur.start_x = j;
				cur.start_y = i;
			}
		}
	}
	finish = false;
	cur.g = 0;
	genSolvePuzzle(size_p);
	cur.h = init_Manhattan(&cur);
	std::cout << "h = " << cur.h << std::endl;
	open.insert(cur);
	printPole(&cur);
	//getNeighbours(&cur);
	// for (auto i : n) {
	// 	print(RED, "Var h: ");
	// 	std::cout << i.h << std::endl;
	// 	printPole(i);
	// }
	int i = 0;
	while (open.size() > 0 && finish == false && i < 300) {
		cur = min_f();
		if (cur.h == 0) {
			std::cout << "puzzle solved\n";
			break ;
		}
		close.insert(cur);
		open.erase(cur);
		getNeighbours(&cur);
		for (auto i : n) {
			print(RED, "Var h: ");
			std::cout << i.h << std::endl;
			printPole(&i);
		}
		i++;
	}
	// 1) Определите ОТКРЫТЫЙ список.
	//Изначально OPEN состоит исключительно из одного узла, начального узла S.

	// 2) Если список пуст, верните ошибку и завершите работу.
	//dict[graph[0]] = 1;

	// 3) Удалите узел n с наименьшим значением f(n) из ОТКРЫТОГО списка и переместите его в список ЗАКРЫТЫХ.
	// Если узел n является целевым состоянием, верните success и завершите работу.

	// 4) Разверните узел n.

	// 5) Если какой-либо преемник n является целевым узлом, верните success и решение, проследив путь от целевого узла до S.
	// В противном случае перейдите к шагу-06.

	// 6) Для каждого последующего узла, Примените вычислительную функцию f к узлу.
	//Если узла не было ни в одном из списков, добавьте его в OPEN.

	// 7) Go back to Step-02. 

}