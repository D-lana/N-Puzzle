#include "Library.hpp"
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <vector>
#include <deque>

struct Puzz {
	std::vector<std::vector<int>> graph;
	int g;
	int h;
	int start_x;
	int start_y;
	int prev_x;
	int prev_y;
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
std::deque<Puzz> result;
int count_in_time;
int count_in_size;

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
	// for (size_t i = 1; i < solve.size(); i++) {
	// 	for (size_t j = 1; j < solve[i].size(); j++) {
	// 		std::cout << solve[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// std::cout << std::endl;
}

std::ifstream cin("input.txt");
int size_p;

bool finish;

template<>
struct std::hash<Puzz>
{
	std::size_t operator()(Puzz const& s) const noexcept
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

std::unordered_set<Puzz> open;
std::unordered_set<Puzz> close;
std::vector<Puzz> neighbours;
std::vector<Puzz> n;

Puzz min_f(Puzz cur) {
	int min = INT_MAX;
	Puzz min_p;
	for (auto it : open) {
		if (it.h + it.g < min) {
			min = it.h + it.g;
			min_p = it;
		}
	}
	count_in_time++;
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
	Puzz puzz_min_g;
	tmp.g++;
	tmp.prev_x = s_x;
	tmp.prev_y = s_y;
	int num = 0;
	if (x > 0 && y > 0 && x + 1 <= puz->graph.size() && y + 1 <= puz->graph.size()) {
		//std::cout << "addNeighbour > " << x << " " << y << "\n";
		std::swap(tmp.graph[y][x], tmp.graph[s_y][s_x]);
		num = tmp.graph[s_y][s_x];
		tmp.h = tmp.h - h_Manhattan(num, x, y) + h_Manhattan(num, s_x, s_y);
		//std::cout << "for " << num << "= - " << h_Manhattan(num, x, y);
		//std::cout << " + " << h_Manhattan(num, s_x, s_y);
		//std::cout << ", h = " << tmp.h << std::endl;
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
					//std::cout << "g change " << puzz_min_g.g << " to " << tmp.g << std::endl;
				}
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

void printResult(Puzz cur) {
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

void complexityInSize() {
	int new_size = close.size() + open.size();
	if (count_in_size < new_size) {
		count_in_size = new_size;
	}
}

int main() { 
	count_in_time = 0;
	count_in_size = 0;
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
	cur.prev_x = 0;
	cur.prev_y = 0;
	cur.g = 0;
	genSolvePuzzle(size_p);
	cur.h = init_Manhattan(&cur);
	//std::cout << "h = " << cur.h << std::endl;
	open.insert(cur);
	//printPole(&cur);
	// for (auto i : n) {
	// 	print(RED, "Var h: ");
	// 	std::cout << i.h << std::endl;
	// 	printPole(i);
	// }
	while (open.size() > 0 && finish == false) {
		cur = min_f(cur);
		//std::cout << "h = " << cur.h;
		//std::cout << ", g = " << cur.g << std::endl;
		if (cur.h == 0) {
			print(GREEN, "\n-------- PUZZLE SOLVED! --------\n\n");
			finish == true;
			break ;
		}
		close.insert(cur);
		open.erase(cur);
		complexityInSize();
		getNeighbours(&cur);
	}
	int x = 0;
	int y = 0;
	while (cur.prev_x != 0) {
		result.push_front(cur);
		std::swap(cur.graph[cur.prev_y][cur.prev_x], cur.graph[cur.start_y][cur.start_x]);
		if (close.find(cur) == close.end()) {
			std::cout << "ERROR!" << std::endl;
			return 0;
		}
		else {
			cur = *close.find(cur);
		}
	}
	printResult(cur);
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

/* Считаем манхетенское расстояние по дефолту
Считаем количество линейных конфликтов и для каждого прибавляем +2
Считаем угловые конфликты 
---Считаем условие последней позиции (если 12 не находится в нижней строке
---или если 15 находится не в последнем столбце) - для рядовой последовательности
Bidirectional search - двунаправленный поиск от запутанного состояния до решения 
и наоборот от решенного пазла к данному запутанному состоянию
Beam search - отсекаем часть невыгодных вариантов - путь становится не кратчайшим, 
но зато экономятся ресурсы памяти и времени
*/