GCCG = gcc
FLAGS= -Wall -Werror -Wextra -std=c11 -g # <== flag
GCOV_FLAG = -fprofile-arcs -ftest-coverage -fPIC

all: clean build

build:
	${GCCG} ${FLAGS} -g _sscanf.c _sscanf.h -o main
	./main

clean:
	rm -rf test *.dSYM main _sscanf

test: clean make_tests
	${GCCG} ${FLAGS} _sscanf.c test.c -lcheck -lm -o test
	./test

report: clean g_sscanf
	./test
	lcov -t "scanf_test" -o test_rez.info -c -d .
	genhtml --ignore-errors unmapped,unmapped -o report test_rez.info # <=== тут штука, чтобы не ругалась на сгенеренный код
	rm *.gcda *.gcno *.info
	open report/index.html

g_sscanf:
	${GCCG} ${FLAGS} ${GCOV_FLAG} -g _sscanf.c test.c -lcheck -lm -o test

tests_valgrind_gcov: report
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=res_leak.txt ./test
	grep -e ERROR res_leak.txt
	rm -rf *.gcda

make_tests:
	checkmk clean_mode=0 tests/*.check > test.c

style:
	clang-format -i *.c *.h
	clang-format -n *.c *.h