#include "Library.hpp"
#include <unordered_map>
#include <unordered_set>
#include <limits.h>
#include <vector>

struct Puzz {
	public:
		std::vector<std::vector<int>> graph;
		int g;
		int h;
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

template<>
struct std::hash<Puzz>
{
	std::size_t operator()(Puzz const& s) const noexcept
	{
		long long hash = 0;
		if (s.graph.size() < 5) {
			for (size_t i = 0; i < s.graph.size(); i++) {
				for (size_t j = 0; j < s.graph[i].size(); j++) {
					hash += s.graph[i][j];
					hash = hash * 10;
				}
			}
		}
		else {
			int k = (s.graph.size() / 3);
			if (k <= 1) k = 2;
			for (size_t i = 0; i < s.graph.size(); i++) {
				for (size_t j = 0; j < s.graph[i].size(); j++) {
					if (i / k == 0 && j / k == 0) {
						hash += s.graph[i][j];
						hash = hash * 10;
					}
				}
			}
		}
		std::cout << "hash = " <<  hash << std::endl;
		return hash;
	}
};

std::ifstream cin("input.txt");
std::unordered_set<Puzz> open;
std::vector<std::vector<int>> graph;

void printPole(Puzz p) {
	for (size_t i = 0; i < p.graph.size(); i++) {
		for (size_t j = 0; j < p.graph[i].size(); j++) {
			std::cout << p.graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main() { 
	int size_p = 0;
	cin >> size_p;
	int m = 0;
	Puzz tmp;
	tmp.graph.resize(size_p);
	for (short i = 0; i < size_p; i++) {
		for (short j = 0; j < size_p; j++) {
			cin >> m;
			tmp.graph[i].push_back(m);
		}
	}
	printPole(tmp);
	open.insert(tmp);
	Puzz tmp2 = tmp;
	std::swap(tmp2.graph[0][0], tmp2.graph[0][1]);
	open.insert(tmp2);
	Puzz tmp3 = tmp2;
	std::swap(tmp3.graph[0][1], tmp3.graph[0][2]);
	open.insert(tmp3);
	std::cout << open.size() << std::endl;
	std::cout << std::endl;
	printPole(tmp2);
	std::cout << std::endl;
	printPole(tmp3);
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