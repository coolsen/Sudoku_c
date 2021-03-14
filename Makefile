CC=gcc -Wall -O3 -g 

Sudoku_c :	Sudoku_c.o

fork:		fork.o

edit:
	emacs  Sudoku_c.c fork.c sudoku20.sud Makefile

run:
	perf stat ./Sudoku_c

runf2:
	perf stat ./fork2.sh

runf4:
	perf stat ./fork4.sh

runf8:
	perf stat ./fork8.sh

clean:
	rm -f Sudoku_c Sudoku_c.o fork fork.o core
