CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	lsort test_list test_node measure

all:		$(TARGETS)


node.o:		node.h list.h node.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o node.o node.c

list.o:		node.h list.h list.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -list.o list.c

test_node.o:	node.h list.h node.h test_node.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o test_node.o test_node.c

test_list.o:	node.h list.h test_list.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o test_list.o test_list.c

lsort.o:	node.h list.h lsort.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o lsort.o lsort.c


liblist.a:	node.o list.o
	@echo "Linking $@..."
	@ $(AR) $(ARFLAGS) liblist.a node.o list.o


test_node:	liblist.a test_node.o
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o test_node test_node.o liblist.a
	
test_list:	liblist.a test_list.o
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o test_list test_list.o liblist.a

lsort:		liblist.a lsort.o
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o lsort lsort.o liblist.a

measure.o:	measure.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o measure.o measure.c

measure:	measure.o
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o measure measure.o

test:		test-node test-list test-lsort benchmark

benchmark:	measure
	@echo "Running benchmark..."
	@./benchmark.py
	

test-node:	test_node
	@echo Testing node...
	@[ `valgrind --leak-check=full ./test_node 2>&1 | tee test_node.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_node.log

test-list:	test_list
	@echo Testing list...
	@[ `valgrind --leak-check=full ./test_list 2>&1 | tee test_list.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_list.log

test-lsort:	lsort test_lsort.sh
	@echo Testing lsort...
	@./test_lsort.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_node test_list *.a *.o *.log *.input

.PHONY:		all test test-node test-list test-lsort clean
