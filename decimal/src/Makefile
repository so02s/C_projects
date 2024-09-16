#Флаги
GCC= gcc -c
GCCG= gcc
FLAGS= -Wall -Werror -Wextra -std=c11
LFLAGS = -Wall -Werror -Wextra -g -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector -fanalyzer
TEST_LIBS=-lcheck -lpthread -fprofile-arcs -ftest-coverage #-lsubunit -pthread -lrt -lm
GCOV_FLAGS= -fprofile-arcs -ftest-coverage -fPIC

ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck_pic -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN_CM=open
endif

#файлы проекта
F_H= _decimal.h
F_C= functions/*/*.c
#файлы тестов

FT_C= tests/tests.c 
FT_CH= tests/*/*.check # arithmetic
SOURCE_TESTS= -lcheck -o test # -pthread -lcheck_pic -pthread -lrt -lm -lsubunit  // флаги сообщающие путь к библиотеке check  убунту

#======================================== ALL =========================================================================
all: clean gcov_report

# ======================================= Компиляция тестов ===========================================================
test: clean _decimal.a make_tests
	${GCCG} ${FLAGS} ${SOURCE_TESTS} ${FT_C} _decimal.a ${LDFLAGS} 
	./test

make_tests:
	checkmk clean_mode=1 $(FT_CH) > $(FT_C)
	clang-format -i $(FT_C)

amogus: clean _decimal.a
	rm -rf conversation_test.c
	checkmk clean_mode=1 tests/arithmetic/_mul.check > conversation_test.c
	clang-format -i conversation_test.c
	$(GCCG) $(FLAGS) $(LDFLAGS) ${SOURCE_TESTS} _decimal.a conversation_test.c
	./test

amogus2: clean
	gcc ${FLAGS} ${F_C} main.c -g
	 ./a.out

# ======================================= Вывод тестов в HTML отчет ===================================================

gcov_report: clean g_decimal.a make_tests
	${GCCG} ${FLAGS} ${FT_C} _decimal.a ${SOURCE_TESTS} ${LDFLAGS} ${GCOV_FLAGS}
	./test
	-lcov -t "decimal_tests" -o test_rez.info -c -d .
	-genhtml -o report test_rez.info
	rm *.gcda *.gcno *.info
	-open report/index.html

# ======================================= Тесты на утечки (которых в decimal нет) =============================================================
tests_valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=res_leak.txt ./test
	grep -e ERROR res_leak.txt
	rm -rf *.gcda
tests_valgrind_gcov: gcov_report
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=res_leak.txt ./test
	grep -e ERROR res_leak.txt
	rm -rf *.gcda

leaks: clean _decimal.a make_tests
	valgrind --tool=memcheck --leak-check=yes  ./a.out
	leaks -atExit -- ./test
	$(GCCG) $(LFLAGS) ${SOURCE_TESTS} tests/*.c  _decimal.a -o 1
	./1
# ======================================= Сборка библиотеки в файл _decimal.a =========================================
_decimal.a: clean
	${GCC} ${FLAGS} ${F_C}
	ar rc _decimal.a *.o
	ranlib _decimal.a
	make clean.o

g_decimal.a: clean
	${GCC} ${FLAGS} ${F_C} ${GCOV_FLAGS}
	ar rc _decimal.a *.o
	ranlib _decimal.a
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
	rm -rf *.o
clean.a:
	rm -rf *.a
clean.gcno:
	rm -rf *.gcno
clean.gcda:
	rm -rf *.gcda
clean:
	rm -rf *.o *.out *.a
	rm -rf test ./tests/tests.c
	rm -rf *.gcno *.gcda *.gcov
	rm -rf *.txt *.html *.css
	rm -rf report
	rm -rf main
	rm -rf conversation_test.c
