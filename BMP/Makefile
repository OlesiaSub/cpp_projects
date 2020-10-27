CFLAGS=-Iinclude -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak

all: hw_01

hw_01: obj/bmp.o obj/main.o
	gcc -g -o hw_01 $(CFLAGS) obj/bmp.o obj/main.o

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc -g -c $(CFLAGS) src/bmp.c -o obj/bmp.o

obj/main.o: src/main.c include/bmp.h | obj
	gcc -g -c $(CFLAGS) src/main.c -o obj/main.o

obj:
	mkdir obj/

clean:
	rm -rf obj
	rm -rf hw_01
