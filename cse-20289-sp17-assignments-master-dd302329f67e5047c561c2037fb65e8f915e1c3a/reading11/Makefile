CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.	
TARGETS=	ncat

all:		$(TARGETS)

%.o:		%.c		
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $<

ncat:		ncat.o
	@echo Linking $@...
	@ $(LD) $(LDFLAGS) -o $@ $<
	
clean:
	rm -f $(TARGETS) *.o
