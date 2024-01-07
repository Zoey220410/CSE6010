solution: main.o execute.o 
	gcc -o instructions main.o execute.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o instructions
