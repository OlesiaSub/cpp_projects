CFLAGS = -Iinclude -std=c++17 -Wall -Wextra -Werror

all: lab_14

lab_14: obj/main.o obj/matrix.o | obj
	g++ -g -o lab_14 $(CFLAGS) obj/matrix.o obj/main.o

obj/matrix.o: src/matrix.cpp include/matrix.h | obj
	g++ -g -c $(CFLAGS) src/matrix.cpp -o obj/matrix.o

obj/main.o: src/main.cpp include/matrix.h | obj
	g++ -g -c $(CFLAGS) src/main.cpp -o obj/main.o

obj:
	mkdir obj

clean:
	rm -rf obj lab_14 *.edb
