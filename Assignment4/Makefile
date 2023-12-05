solution: main.o processCollisions.o processParticles.o insertSort.o
	gcc -o particles main.o processCollisions.o processParticles.o insertSort.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o particles
