SHELL= bash

all: solve

solve: Board.o solve.cpp
	@echo "Making executable..."
	@ g++ -Wall solve.cpp Board.o -o solve	

test:	solve
	@echo "Testing easy puzzle..."
	@ diff <(./solve puzzles/easy.txt) solutions/easySol.txt 2>&1>/dev/null || \
	    (echo "easy test failed" && exit 1)
	@echo "Testing medium puzzle..."
	@ diff <(./solve puzzles/medium.txt) solutions/mediumSol.txt 2>&1>/dev/null || \
	    (echo "medium test failed" && exit 1)
	@echo "Testing challenge puzzle ..."
	@ diff <(./solve puzzles/challenge.txt) solutions/challengeSol.txt 2>&1>/dev/null || \
	    (echo "challenge test failed" && exit 1)

Board.o: Board.h Board.cpp Cell.h
	@echo "Compiling Board.o..."
	@ g++ -Wall -c Board.cpp
clean:
	@echo "Cleaning..."
	@ rm *.o solve
