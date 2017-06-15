CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
TARGETS=	final

all:		$(TARGETS)

$(TARGETS): final.o
	@echo "Linking $@..."
	@$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $^

test: $(TARGETS)
	./final

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

