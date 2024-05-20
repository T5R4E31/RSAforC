main: prime_func.o
	gcc -Wall prime_func.o main.c -o main

prime_func.o:
	gcc -Wall -c prime_func.c

clean:
	rm -rf *.o main
