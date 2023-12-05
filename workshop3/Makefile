solution: diameter.o 
	gcc -o res diameter.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o res
