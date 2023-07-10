CC = g++

CFLAG = -c
OFLAG = -o
CLEAN_FLAGS = -Wall -Werror -Wextra -std=c++17
GCOV_FLAGS = -lgcov --coverage
TEST_FLAGS = -lgtest

HEAD = code/s21_*.h
CODE = code/s21_*.cc
T_CODE = tests/test_file.cc
OBJ = code/obj/s21_*.o
T_OBJ = tests/obj/test_file.o
LFILE = s21_matrix_oop.a
T_LFILE = tests/test_file.a

GCNO = covers/*.gcno
GCDA = covers/*.gcda
REPORT_FILES = *.css *.html
T_BIN = tester

all: gcov_report

s21_matrix_oop.a: clean
	$(CC) $(CLEAN_FLAGS) $(CFLAG) $(CODE)
	mkdir code/obj
	mv s21_*.o code/obj 
	ar rc $(LFILE) $(OBJ)
	ranlib $(LFILE)

test: s21_matrix_oop.a
	$(CC) $(CLEAN_FLAGS) $(CFLAG) $(T_CODE)
	mkdir tests/obj
	mv *.o tests/obj
	ar rc $(T_LFILE) $(T_OBJ)
	ranlib $(T_LFILE)
	$(CC) $(CLEAN_FLAGS) $(GCOV_FLAGS) $(OFLAG) $(T_BIN) $(LFILE) $(T_LFILE) $(CODE) $(TEST_FLAGS)
	./tester
	mkdir covers
	mv *.gcda covers
	mv *.gcno covers

leaks: test
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(HEAD) $(CODE) $(T_CODE) --verbose
	cppcheck --language=c++ $(HEAD) $(CODE) $(T_CODE)
	valgrind -s --leak-check=full ./$(T_BIN)

gcov_report: test
	mkdir html
	gcov $(GCDA)
	gcovr 
	gcovr --html-details html/coverage.html
	mv *.gcov covers
	firefox html/coverage.html

clean:
	rm -rf tester covers html $(LFILE) $(T_LFILE) code/obj tests/obj *.gcno *.gcda *.o .clang-format