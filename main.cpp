#include "Library.hpp"
#include <chrono>

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
		pSolver.initDistance();
		auto begin = std::chrono::steady_clock::now();
		//--------
		//pSolver.startAlgorithmAStar();
		//--------
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		print(BLUE, "The time: ");
		std::cout << elapsed_ms.count() << " ms\n";
		//pSolver.h(3, 1);
	}
	puzzle.printPole();
}
