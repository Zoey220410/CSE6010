solution: shortpath.o 
	gcc -o bellmanford shortpath.o -lm -fopenmp -O3

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o bellmanford
