CC=gcc 

Sudoku_c :	Sudoku_c.o

fork:		fork.o

edit:
	gedit Sudoku_c.c fork.c sudoku20.sud

run:
	perf stat ./Sudoku_c

clean:
	rm -f Sudoku_c Sudoku_c.o fork fork.o
