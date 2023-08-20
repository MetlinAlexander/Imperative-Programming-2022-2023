all: app
clean:
	rm app main.o primes.o
app: main.o primes.o
	gcc main.o primes.o -o app
main.o: main.c primes.h
	gcc -c main.c -o main.o
primes.o: primes.c primes.h
	gcc -c primes.c -o primes.o