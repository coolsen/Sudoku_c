CC=gcc 

Sudoku_c :	Sudoku_c.o 

edit:
	gedit Sudoku_c.c
run:
	perf stat ./Sudoku_c

clean:
	rm -f Sudoku_c Sudoku_c.o
