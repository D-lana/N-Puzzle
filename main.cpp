#include "Library.hpp"
#include <chrono>

// g - стоимость пройденного пути
// h - стоимость оставшегося пути


void parserArgv(int argc, char **argv) {
	if (argc > 2) {	
		std::string arg_1(argv[1]);
		if (arg_1 == "-h") {
			print(BLUE, "ADD heuristic");
		}
	}
	else {
		//error(RED, 1);
	}
}

int main(int argc, char **argv) {
	parserArgv(argc, argv);
	PuzzleParser parser("input.txt");
	if (parser.readFile() == FAIL 
	||	parser.checkNum() == FAIL
	|| parser.checkSolution() == FAIL) {
		return (-1);
	}
	parser.printPole();
	parser.printInLine();
	if (parser.getStatus() == READY) {
		Puzzle puzzle(parser.getGraph());
		PuzzleSolver pSolver(puzzle);
		pSolver.genSolvePuzzle(parser.getSize());
		pSolver.runAlgorithm(puzzle);
	}
}
