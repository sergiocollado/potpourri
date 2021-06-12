
all : lib test

crypt.o : crypt.c crypt.h
	gcc -O2 -c -fPIC -Wall crypt.c

lib : crypt.o 
	gcc -shared -Wl,-soname,libcrypt.so.1 -o libcrypt.so.1.0.1 crypt.o -lc
	ln -sf libcrypt.so.1.0.1 libcrypt.so

test.o : test.c crypt.h
	gcc -Wall -O2 -c test.c

test : test.o crypt.o
	gcc -Wall -o test test.o crypt.o

clean : 
	rm *.o; rm libcrypt.so*; rm test
