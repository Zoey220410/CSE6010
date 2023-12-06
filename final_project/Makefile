solution: main.o execute.o 
	gcc -o instructions main.o execute.o

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o instructions
