GCC= gcc
FLAGS= -Wall -Werror -Wextra -std=c11 -g
LFLAGS = -Wall -Werror -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector -fanalyzer
GCOV_FLAGS= -fprofile-arcs -ftest-coverage -fPIC

ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck_pic -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN_CM=open
endif

F_H= _matrix.h
F_C= func/*.c

FT_C= test.c 
FT_CH= test/*.check
SOURCE_TESTS= -lcheck -o testing
TEST= ./testing

#======================================== ALL =========================================================================

all: clean gcov_report


# ======================================= Компиляция тестов ===========================================================

test: clean _matrix.a make_tests
	${GCC} ${FLAGS} ${SOURCE_TESTS} ${FT_C} _matrix.a ${LDFLAGS} 
	${TEST}

make_tests:
	checkmk clean_mode=0 $(FT_CH) > $(FT_C)
	clang-format -i $(FT_C)

simple: clean _matrix.a
	${GCC} ${FLAGS} ${SOURCE_TESTS} main.c _matrix.a ${LDFLAGS} 
	@echo "Running simple tests..."
	# leaks --atExit -- ${TEST}
	${TEST}

# ======================================= Вывод тестов в HTML отчет ===================================================

gcov_report: clean g_matrix.a make_tests
	${GCC} ${FLAGS} ${FT_C} _matrix.a ${SOURCE_TESTS} ${LDFLAGS} ${GCOV_FLAGS}
	${TEST}
	lcov -t "matrix_tests" -o test_rez.info -c -d .
	genhtml -o report test_rez.info --ignore-errors unmapped --ignore-errors unmapped
	rm *.gcda *.gcno *.info
	open report/index.html


# ======================================= Тесты на утечки =============================================================

tests_valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=res_leak.txt ${TEST}
	grep -e ERROR res_leak.txt
	rm -rf *.gcda

tests_valgrind_gcov: gcov_report
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=res_leak.txt ${TEST}
	grep -e ERROR res_leak.txt
	rm -rf *.gcda

leaks: clean _matrix.a make_tests
	valgrind --tool=memcheck --leak-check=yes  ./a.out
	leaks -atExit -- ${TEST}
	$(GCC) $(LFLAGS) ${SOURCE_TESTS} tests/*.c  _matrix.a -o 1
	./1


# ======================================= Сборка библиотеки в файл _matrix.a =======================================

_matrix.a: clean
	${GCC} -c ${FLAGS} ${F_C}
	ar rc _matrix.a *.o
	ranlib _matrix.a
	make clean.o

g_matrix.a: clean
	${GCC} -c ${FLAGS} ${F_C} ${GCOV_FLAGS}
	ar rc _matrix.a *.o
	ranlib _matrix.a
	make clean.o


# ======================================= Работа со стилями в проекте =================================================

cppchecker:
	cppcheck ${F_C} ${F_H} ${FT_C} ${FT_H}

style:
	clang-format -n ${F_C} ${F_H}
	
style_red:
	clang-format -i ${F_C} ${F_H}


# ======================================= Clean =======================================================================

clean.o:
	rm -f *.o

clean:
	rm -rf *.o *.out *.a
	rm -rf test.c
	rm -rf *.gcno *.gcda *.gcov
	rm -rf *.txt *.html *.css
	rm -rf report
	rm -rf testing testing.dSYM