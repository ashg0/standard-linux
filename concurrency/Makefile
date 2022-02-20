iterative: iterative.c
	gcc -o $@ $<

forking: forking.c
	gcc -o $@ $<

all: iterative forking

.PHONY: clean

clean:
	rm -f iterative forking
