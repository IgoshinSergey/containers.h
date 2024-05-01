CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -Werror
LIBS =  -lgtest -lgcov
LINUX = -lrt -lpthread -lm -lsubunit 
LFLAGS = -fprofile-arcs -ftest-coverage 	
OS = $(shell uname -s)



test:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) tests/*.cc -o unit_tests $(LIBS) 
else
	$(CC) $(CFLAGS) tests/*.cc -o unit_tests $(LIBS) $(LINUX) 
endif
	./unit_tests


gcov_report:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) tests/*.cc  -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) tests/*.cc  -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	mkdir report
	gcovr *.gcda
	gcovr -b
	gcovr
	gcovr --html-details -o ./report/report.html
	open ./report/report.html


style:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i *.h
	clang-format -n *.h
	rm -rf .clang-format


valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./unit_tests


clean:
	rm -rf  *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf *.gcov
	rm -rf report
	rm -rf gcov_test
	rm -rf test.out
