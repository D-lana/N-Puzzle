#include "Library.hpp"
#include <chrono>

// g - стоимость пройденного пути
// h - стоимость оставшегося пути


int main() {
	PuzzleParser parser("input.txt");
	if (parser.readFile() == FAIL) {
		error(1);
		return 0;
	}
	if (parser.checkNum() == FAIL) {
		error(2);
		return 0;
	}
	if (parser.checkSolution() == FAIL) {
		return 0;
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
