CFLAGS = -Iinclude -std=c++17 -Wall -Wextra -Werror

all: hw_02 test_hw_02

hw_02: obj/Board.o obj/main.o obj/StdioBoardView.o | obj
	g++ -g -o hw_02 $(CFLAGS) obj/Board.o obj/main.o obj/StdioBoardView.o

test_hw_02: obj/Board.o obj/test.o obj/BoardTest.o obj/main_test.o obj/StdioBoardView.o | obj
	g++ -g -o test_hw_02 $(CFLAGS) obj/Board.o obj/test.o obj/BoardTest.o obj/main_test.o obj/StdioBoardView.o

obj/main.o: src/main.cpp include/Board.h include/StdioBoardView.h | obj
	g++ -g -c $(CFLAGS) src/main.cpp -o obj/main.o

obj/Board.o: src/Board.cpp include/Board.h | obj
	g++ -g -c $(CFLAGS) src/Board.cpp -o obj/Board.o

obj/StdioBoardView.o: src/StdioBoardView.cpp include/StdioBoardView.h | obj
	g++ -g -c $(CFLAGS) src/StdioBoardView.cpp -o obj/StdioBoardView.o

obj/BoardTest.o: test/BoardTest.cpp include/Board.h include/StdioBoardView.h include/BoardTest.h include/Test.h | obj
	g++ -g -c $(CFLAGS) test/BoardTest.cpp -o obj/BoardTest.o

obj/test.o: test/test.cpp include/BoardTest.h include/Test.h | obj
	g++ -g -c $(CFLAGS) test/test.cpp -o obj/test.o

obj/main_test.o: test/main_test.cpp include/BoardTest.h include/Test.h | obj
	g++ -g -c $(CFLAGS) test/main_test.cpp -o obj/main_test.o

obj:
	mkdir obj

clean:
	rm -rf obj hw_02 test_hw_02 *.edb
