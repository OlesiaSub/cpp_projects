CFLAGS=-Wall -Wextra -Werror

all: lab_03

lab_03: obj/clist.o obj/main.o
	gcc -g -Iinclude -o lab_03 $(CFLAGS) obj/clist.o obj/main.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -g -Iinclude -c $(CFLAGS) src/clist.c -o obj/clist.o

obj/main.o: src/main.c include/clist.h | obj
	gcc -g -Iinclude -c $(CFLAGS) src/main.c -o obj/main.o

obj:
	mkdir obj/

clean:
	rm -rf obj
	rm -rf lab_03
