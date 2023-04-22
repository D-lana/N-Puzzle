#include "Library.hpp"
#include <chrono>

// g - стоимость пройденного пути
// h - стоимость оставшегося пути
// В бонусах:
// - h(x) = 0  - это Uniform cost search
// - g(x) = 0 - это Greedy search

Heuristics &getHeuristics(int argc, char **argv, int size_p, e_bonus flag) {
	if (argc > 2 && flag != UNIFORM_COST_SEARCH) {	
		std::string arg_1(argv[2]);
		if (arg_1 == "-h=m") {
			print(BLUE, "heuristic = Manhattan\n");
			Manhattan *m = new Manhattan(size_p);
			return(*m);
		}
		else if (arg_1 == "-h=e") {
			print(BLUE, "heuristic = Euclidean\n");
			Euclidean *e = new Euclidean(size_p);
			return(*e);
		}
		else if (arg_1 == "-h=c") {
			print(BLUE, "heuristic = CountMismatch\n");
			CountMismatch *c = new CountMismatch(size_p);
			return(*c);
		}
		else {
			print(RED, "Unknown heuristic!\n");
		}
	}
	if (flag != UNIFORM_COST_SEARCH) {
		print(BLUE, "Set default heuristic = Manhattan\n");
	}
	Manhattan *m = new Manhattan(size_p);
	return(*m);
}

e_bonus getBonusFlag(int argc, char **argv) {
	int			i = argc - 1;
	e_bonus		flag = NO_BONUS;
	std::string	arg_1(argv[i]);
	if (arg_1 == "-h=0") {
		flag = UNIFORM_COST_SEARCH;
	}
	else if (arg_1 == "-g=0") {
		flag = GREEDY_SEARCH;
	}
	return(flag);
}

int main(int argc, char **argv) {
	std::string	file = "";
	if (argc < 2) {
		printHelp();
		return (0);
	}
	else {
		file.append(argv[1]);
	}
	PuzzleParser parser(file);
	if (parser.readFile() == FAIL 
	||	parser.checkNum() == FAIL
	|| parser.checkSolution() == FAIL) {
		return (-1);
	}
	if (parser.getStatus() == READY) {
		auto begin = std::chrono::steady_clock::now();
		int size_p = parser.getSize();
		e_bonus flag = getBonusFlag(argc, argv);
		Heuristics &h = getHeuristics(argc, argv, size_p, flag);
		Puzzle puzzle(parser.getGraph());
		PuzzleSolver pSolver(puzzle, h, flag);
		pSolver.runAlgorithm(puzzle);
		delete &h;
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		print(GRAY, "The total time: ");
		print(BLUE, std::to_string(elapsed_ms.count()) + " ms\n\n");
	}
}
