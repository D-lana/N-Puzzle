#include "Library.hpp"

// g - стоимость пройденного пути
// h - стоимость оставшегося пути

int main() {
	Puzzle puzzle("input.txt");
	if (puzzle.parser() == FAIL) {
		puzzle.~Puzzle();
		error(1);
	}
	if (puzzle.checkNum() == FAIL) {
		puzzle.~Puzzle();
		error(2);
	}
	if (puzzle.checkSolution() == FAIL) {
		puzzle.~Puzzle();
		error(3);
	}
	puzzle.printPole();
	puzzle.printInLine();
	if (puzzle.getStatus() == READY) {
		PuzzleSolver pSolver(puzzle);
		pSolver.genSolvePuzzle();
		pSolver.startAlgorithmAStar();
		pSolver.h(3, 1);
	}
	
}
