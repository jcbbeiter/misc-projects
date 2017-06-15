CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	freq

all:		$(TARGETS)


freq.o:		freq.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ freq.c

test_entry.o:	test_entry.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ test_entry.c

test_fnv.o:	test_fnv.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ test_fnv.c

test_map.o:	test_map.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ test_map.c


entry.o:	entry.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ entry.c

fnv.o:		fnv.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ fnv.c

map.o:		map.c map.h
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ map.c

libmap.a:	entry.o fnv.o map.o
	@echo "Linking $@..."
	@ $(AR) $(ARFLAGS) $@ entry.o fnv.o map.o

freq:		freq.o libmap.a
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o $@ $?
test_entry:	test_entry.o libmap.a
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o $@ $?
test_fnv:	test_fnv.o libmap.a
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o $@ $?
test_map:	test_map.o libmap.a
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o $@ $?

measure.o:	measure.c
	@echo "Compiling $@..."
	@ $(CC) $(CFLAGS) -c -o $@ $?

measure:	measure.o
	@echo "Linking $@..."
	@ $(LD) $(LDFLAGS) -o $@ $?
	

test:		test-entry test-fnv test-map test-freq

test-entry:	test_entry
	@echo Testing entry...
	@[ `valgrind --leak-check=full ./test_entry 2>&1 | tee test_entry.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_entry.log || cat test_entry.log

test-fnv:	test_fnv
	@echo Testing fnv...
	@[ `valgrind --leak-check=full ./test_fnv 2>&1 | tee test_fnv.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_fnv.log || cat test_fnv.log

test-map:	test_map
	@echo "Testing map..."
	@[ `valgrind --leak-check=full ./test_map 2>&1 | tee test_map.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_map.log || cat test_map.log

test-freq:	test_freq.sh freq
	@echo "Testing freq..."
	@./test_freq.sh 2>&1 | tee test_freq.log
	@[ `valgrind --leak-check=full ./freq < map.h 2>&1 | tee test_freq.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_freq.log || cat test_freq.log

benchmark:	measure freq benchmark.py
	@echo Benchmarking
	@./benchmark.py

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_entry test_fnv test_map measure *.a *.o *.log *.input

.PHONY:		all test benchmark clean
