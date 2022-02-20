iterative: iterative.c
	gcc -o $@ $<

forking: forking.c
	gcc -o $@ $<

preforked: preforked.c
	gcc -o $@ $<

threaded: threaded.c
	gcc -o $@ $< -lpthread

prethreaded: prethreaded.c
	gcc -o $@ $< -lpthread

all: iterative forking preforked threaded prethreaded

.PHONY: clean

clean:
	rm -f iterative forking preforked threaded prethreaded
