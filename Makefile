CFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17
SOURCE_TEST = s21_matrix_oop_tests.cc
TESTS = s21_matrix_oop_tests.o
SOURCES = s21_matrix_oop.cc
MATRIXFUNC = $(SOURCES:.cc=.o)
S21MATRIXOOPLIB = s21_matrix_oop.a

OBJECTS = $(SOURCES:.cc=.o)
FLAGS = -lgtest -lgtest_main -pthread

all: test

hello: s21_matrix_oop.o
	g++ s21_matrix_oop.o -o hello

s21_matrix_oop.o: s21_matrix_oop.cc s21_matrix_oop.h
	g++ -c s21_matrix_oop.cc

test: $(TESTS) $(S21MATRIXOOPLIB)
	g++ s21_matrix_oop_tests.cc s21_matrix_oop.cc -o test $(FLAGS)
	./test

$(TESTS): $(TESTS:.o=.cc)
	g++ $(CFLAGS) -c $^  -o $@

s21_matrix_oop.a: $(MATRIXFUNC)
	ar rc $(S21MATRIXOOPLIB) $^
	ranlib $(S21MATRIXOOPLIB)

rebuild: clean all

gcov_report: clean $(TESTS)
	g++  -o test $(SOURCE_TEST) --coverage $(SOURCES) $(FLAGS)
	./test
	lcov -t "a.out" -o test.info -c -d .
	lcov --remove test.info '/usr/local/include/c++/10.3.0/*' '/usr/local/include/gtest/*' -o test_filtered.info 
	genhtml -o report test_filtered.info
	open ./report/index.html
	rm -rf test *.o *.a *gcda *gcno *info

clean:
	rm -rf test *.o *.a *.gch *gcda *gcno *info hello report