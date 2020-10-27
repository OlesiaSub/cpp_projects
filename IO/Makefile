CFLAGS=-Iinclude -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak

all: lab_05

lab_05: obj/point_list.o obj/clist.o obj/main.o
	gcc -g -o lab_05 $(CFLAGS) obj/point_list.o obj/main.o obj/clist.o

obj/clist.o: src/clist.c include/clist.h | obj
	gcc -g -c $(CFLAGS) src/clist.c -o obj/clist.o

obj/main.o: src/main.c include/point_list.h include/clist.h | obj
	gcc -g -c $(CFLAGS) src/main.c -o obj/main.o

obj/point_list.o: src/point_list.c include/point_list.h include/clist.h | obj
	gcc -g -c $(CFLAGS) src/point_list.c -o obj/point_list.o

obj:
	mkdir obj/

clean:
	rm -rf obj
	rm -rf lab_05
