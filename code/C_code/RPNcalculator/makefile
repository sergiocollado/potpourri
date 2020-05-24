# basic make file for the reverse polish notation calculator. v1
# remeber to use tabs!!

# the rules in 'make' has the following format:

# target: [dependecies]
# \tab command

CC = gcc
OBJECTS = stack.o getop.o getch.o

polishcalc : main.o $(OBJECTS)
	$(CC) -o polishcalc  main.o $(OBJECTS)
main.o: main.c calc.h
	$(CC) -c main.c
stack.o: stack.c calc.h
	$(CC) -c stack.c
getop.o: getop.c calc.h
	 $(CC) -c getop.c
getch.o: getch.c
	$(CC) -c getch.c
clean:
	 rm polishcalc \
	 main.o stack.o getop.o getch.o
