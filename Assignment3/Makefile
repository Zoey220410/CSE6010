solution: main.o 
	gcc -o connected main.o

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o connected
