CC=gcc -O3

Sudoku_c :	Sudoku_c.o

fork:		fork.o

edit:
	gedit Sudoku_c.c fork.c sudoku20.sud

run:
	perf stat ./Sudoku_c

runf4:
	perf stat ./fork4.sh

clean:
	rm -f Sudoku_c Sudoku_c.o fork fork.o
