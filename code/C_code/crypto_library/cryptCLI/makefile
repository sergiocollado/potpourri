
DEFAULT_LIB_INSTALL_PATH = ../cryptolib

all : main.o common_functions.o
	gcc -Wall -O3 -o crypt common_functions.o main.o -rdynamic -ldl -Wl,-rpath,$(DEFAULT_LIB_INSTALL_PATH)

main.o : main.c
	gcc -Wall -O3 -c main.c

common_functions.o : common_functions.c common_functions.h
	gcc -Wall -O3 -c common_functions.c 
clean : 
	rm *.o; rm crypt;

install : 
	sudo cp ./crypt /usr/local/bin/crypt
