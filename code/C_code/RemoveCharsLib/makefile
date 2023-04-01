help:
	@echo 'use "make ar" to build as a static library or "make so" as a shared library'

main: main.o
	gcc -c main.c

ar: main.o
	gcc -c removeChars.c \
	&& ar rcs libRemoveChars.a removeChars.o && ranlib libRemoveChars.a \
	&& echo 'Simbols: ' && nm libRemoveChars.a \
	&& ar -t libRemoveChars.a \
	&& gcc main.o -L. -lRemoveChars -o myprog
	# reference:
	#  - https://dev.to/iamkhalil42/all-you-need-to-know-about-c-static-libraries-1o0b
	#  - https://makori-mildred.medium.com/how-to-create-static-library-in-c-and-how-to-use-it-b8b3e1fde999

so: main.o
	gcc -c removeChars.c -fPIC  &&  \
	gcc removeChars.o -shared -o libRemoveChars.so  && \
	gcc main.o  -L. -l RemoveChars -I. -o myprog
	#export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD) \
	#echo 'Please, run the previous line in the terminal'

clean:
	@rm myprog *.o *.a *.gch *.so


#linking options: https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html#Link-Options
