all: app
clean:
	rm app main.o modular.o
app: main.o modular.o
	gcc main.o modular.o -o app
main.o: main.c modular.h
	gcc -c main.c -o main.o
modular.o: modular.c modular.h
	gcc -c modular.c -o modular.o