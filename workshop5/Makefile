solution: pi.o
	gcc -o pi pi.o -fopenmp -O3

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o pi
