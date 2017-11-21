all: pipe.c
	gcc -o pipeleak pipe.c
run: all
	./pipeleak
clean:
	rm *~