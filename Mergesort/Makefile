CFLAGS=-Iinclude -Wall -Wextra -Werror -pedantic

all: lab_04

lab_04: obj/mergesort.o obj/main.o obj/my_memcpy.o
	gcc -g -o lab_04 $(CFLAGS) obj/mergesort.o obj/main.o obj/my_memcpy.o

obj/mergesort.o: src/mergesort.c include/mergesort.h include/my_memcpy.h | obj
	gcc -g -c $(CFLAGS) src/mergesort.c -o obj/mergesort.o

obj/main.o: src/main.c include/mergesort.h include/my_memcpy.h | obj
	gcc -g -c $(CFLAGS) src/main.c -o obj/main.o

obj/my_memcpy.o: src/my_memcpy.c include/my_memcpy.h | obj
	gcc -g -c $(CFLAGS) src/my_memcpy.c -o obj/my_memcpy.o

obj:
	mkdir obj/

clean:
	rm -rf obj
	rm -rf lab_04
