solution: main.o pq.o
	gcc -o pq main.o pq.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o pq
