#include "Library.hpp"
#include <chrono>

// g - стоимость пройденного пути
// h - стоимость оставшегося пути

Heuristics &getHeuristics(int argc, char **argv, int size_p) {
	if (argc > 2) {	
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
	print(BLUE, "Set default heuristic = Manhattan\n");
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
	std::string file = "";
	if (argc < 2) {
		print(YELLOW, "Please, enter the following arguments:\n");
		print(YELLOW, "necessary arg:\n");
		print(GRAY, "path to the file (input.txt)\n");
		print(YELLOW, "options:\n");
		print(GRAY, "-h=m Manhattan\n-h=e Euclidean\n-h=c Count Mismatch\n");
		print(GRAY, "-g=0 Greedy search\n-h=0 Uniform cost search\n");
		print(GRAY, "Example no bonus: ./n_puzzle input.txt -h=m\n");
		print(GRAY, "Example bonus: ./n_puzzle input.txt -h=m -g=0\n");
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

	int size_p = parser.getSize();
	Heuristics &h = getHeuristics(argc, argv, size_p);
	e_bonus flag = getBonusFlag(argc, argv);
	if (parser.getStatus() == READY) {
		Puzzle puzzle(parser.getGraph());
		PuzzleSolver pSolver(puzzle, h, flag);
		pSolver.runAlgorithm(puzzle);
	}
	delete &h;
}
