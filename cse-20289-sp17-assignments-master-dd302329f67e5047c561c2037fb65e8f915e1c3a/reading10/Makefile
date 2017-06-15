SHELL=	bash

all: walk

walk.o:	walk.c
	@echo Compiling $@...
	@ gcc -g -gdwarf-2 -Wall -std=gnu99 -c -o $@ walk.c

walk:	walk.o
	@echo Linking $@...
	@ gcc -L. -o $@ walk.o

test:	walk walk.py
	@echo Testing walk...
	@diff <(./walk | sort) <(./walk.py | sort) > walk.log
	@[ `valgrind --leak-check=full ./walk 2>&1 | tee -a walk.log | grep ERROR | awk '{print $4}'` = 0 ] && ! grep -q 'failed' walk.log || cat walk.log

clean:
	@echo Cleaning...
	@ rm walk.o walk
