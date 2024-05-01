CC=g++
#<<<<<<< HEAD
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

# =======
# ADD_LIB=-lgtest -lm
# FLAGS=-std=c++17 -Wpedantic -Werror -Wextra -Wall
# GCOV=--coverage
# ASAN=-fsanitize=address -static-libasan -g
# OS=$(shell uname -s)

# ifeq ($(OS), Linux)
# 	LEAK_CHECK=valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all
# 	OPEN_CMD=xdg-open
# else ifeq ($(OS), Darwin)
# 	LEAK_CHECK=leaks -atExit --
# 	OPEN_CMD=open
# endif

# main: clean
# 	g++ main.cpp -o main
# 	./main

# main_asan: clean
# 	g++ $(ASAN) main.cpp -o main
# 	./main

# main_leaks: clean
# 	g++ main.cpp -o main
# 	$(LEAK_CHECK) ./main

# test: clean
# 	$(CC) $(FLAGS) tests/map_test.cpp -o test $(ADD_LIB)
# 	./test

# leaks: clean
# 	$(CC) $(FLAGS) tests/vector_test.cpp -o test $(ADD_LIB) 
# 	$(LEAK_CHECK) ./test

# asan: clean
# 	$(CC) $(FLAGS) $(ASAN) tests/*.cpp -o test $(ADD_LIB) 
# 	./test

# gcov_report:
# 	$(CC) $(FLAGS) $(GCOV) tests/vector_test.cpp -o gcov_test $(ADD_LIB)
# 	./gcov_test
# 	lcov -c -d . --no-external -o gcov_test.info
# 	genhtml -o report gcov_test.info
# 	chmod 777 report/*
# 	$(OPEN_CMD) report/index.html
# 	rm *.gcda *.gcno *.info gcov_test

# clang:
# 	cp ../materials/linters/.clang-format .
# 	clang-format -i *.h tests/*.cpp
# 	rm -rf .clang-format

# clean:
# 	@rm -rf \
# 	*.o \
# 	main \
# 	test \
# 	report

# # .PHONY: 
# >>>>>>> racquebu
