CC_FLAGS=-std=c99 -Wall -Wextra -g -lm

all: sudoku SudokuSolver

clean:
	rm *.o sudoku SudokuSolver

sudoku: sudoku.o readfiles.o makechecks.o
	clang $(CC_FLAGS) sudoku.o readfiles.o makechecks.o -o sudoku

sudoku.o: sudoku.c
	clang $(CC_FLAGS) sudoku.c -c

readfiles.o: readfiles.c
	clang $(CC_FLAGS) readfiles.c -c

makechecks.o: makechecks.c
	clang $(CC_FLAGS) makechecks.c -c

SudokuSolver: SudokuSolver.o
	clang $(CC_FLAGS) SudokuSolver.o -o SudokuSolver

SudokuSolver.o: SudokuSolver.c
	clang $(CC_FLAGS) SudokuSolver.c -c


