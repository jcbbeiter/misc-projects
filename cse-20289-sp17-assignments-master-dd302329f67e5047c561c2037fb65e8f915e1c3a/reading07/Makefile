CC=             gcc
CFLAGS=         -g -gdwarf-2 -Wall -std=gnu99
TARGETS=        sort grep

all:    sort grep        

sort:		sort.c
	$(CC) $(CFLAGS) sort.c -o sort
grep:		grep.c
	$(CC) $(CFLAGS) grep.c -o grep

test:           sort grep test_sort.sh test_grep.sh
	./test_sort.sh
	./test_grep.sh

test_sort.sh:
	curl -O http://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/sh/test_sort.sh
	chmod +x test_sort.sh

test_grep.sh:
	curl -O http://www3.nd.edu/~pbui/teaching/cse.20289.sp17/static/sh/test_grep.sh
	chmod +x test_grep.sh

clean:
	rm -f sort grep test_sort.sh test_grep.sh
