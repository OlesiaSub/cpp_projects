CFLAGS = -Iinclude -std=c++17 -Wall -Wextra -Werror -pedantic

all: lab_11

lab_11: obj/bin_manip.o obj/employees.o obj/main.o | obj
	g++ -g -o lab_11 $(CFLAGS) obj/bin_manip.o obj/employees.o obj/main.o

obj/main.o: src/main.cpp include/employees.h | obj
	g++ -g -c $(CFLAGS) src/main.cpp -o obj/main.o

obj/bin_manip.o: src/bin_manip.cpp include/bin_manip.h | obj
	g++ -g -c $(CFLAGS) src/bin_manip.cpp -o obj/bin_manip.o

obj/employees.o: src/employees.cpp include/employees.h include/bin_manip.h | obj
	g++ -g -c $(CFLAGS) src/employees.cpp -o obj/employees.o

obj:
	mkdir obj

clean:
	rm -rf obj lab_11 *.edb
