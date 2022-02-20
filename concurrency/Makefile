iterative: iterative.c
	gcc -o $@ $<

forking: forking.c
	gcc -o $@ $<

preforked: preforked.c
	gcc -o $@ $<

all: iterative forking preforked

.PHONY: clean

clean:
	rm -f iterative forking preforked
