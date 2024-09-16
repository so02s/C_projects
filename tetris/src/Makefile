CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
FLAGCUR=-lncurses
ASAN=-g -fsanitize=address
TETRIS_LIB=tetris.a
TETRIS_FILES=gui/cli/cli.c game.c tetris.a
FILETEST=tests/*.c brick_game/tetris/*.c
FILEREPORT=_test_report
FILETESTO=_test
DIRREPORT=report
COVFLAG=-fprofile-arcs -ftest-coverage

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TESTFLAGS=-pthread -lcheck -lm
	OPEN_CMD=open
else
	TESTFLAGS=-pthread -lcheck_pic -lrt -lsubunit -lm
	OPEN_CMD=xdg-open
endif	

all: clean install
	./app/tetris

install: tetris.a
	mkdir app 
	$(CC) $(FLAGS) -o app/tetris $(TETRIS_FILES) $(FLAGCUR)

uninstall:
	rm -rf app *.a

clean:
	rm -rf *.o *.a *.gcno *.gcda *.log *.info *.txt *.out app/ \
	$(DIRREPORT) $(FILETESTO) $(FILEREPORT) dist/ app/

dvi:
	$(OPEN_CMD) Tetris.html

dist:
	mkdir dist
	mkdir dist/src
	cp -r brick_game/ tests/ gui/ Makefile *.h *.c Tetris.html dist/src/
	cd ./dist && tar cvzf brick_game.tgz *
	rm -rf dist/src/

test: $(TETRIS_LIB)
	$(CC) $(FLAGS) $(FILETEST) $(TETRIS_LIB) -o $(FILETESTO) $(TESTFLAGS) $(FLAGCUR)
	rm -rf *.o *.a
	./$(FILETESTO)

gcov_report:
	$(CC) $(FLAGS) $(COVFLAG) $(FILETEST) -o $(FILEREPORT) $(TESTFLAGS) $(FLAGCUR)
	./$(FILEREPORT)
	lcov -t "snake" -o test.info -c -d .
	genhtml -o $(DIRREPORT) test.info
	rm -rf *.o *.a *.gcno *.gcda *.info $(FILEREPORT)
	$(OPEN_CMD) $(DIRREPORT)/index.html



asan_t: $(TETRIS_LIB)
	$(CC) $(FLAGS) $(ASAN) $(TETRIS_FILES) $(FLAGCUR)


tetris.a:
	$(CC) $(FLAGS) -c brick_game/tetris/*.c
	ar rcs tetris.a *.o
	ranlib tetris.a
	rm *.o

#style
cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem brick_game/tetris/*.c \
	gui/cli/*.c tests/*.c game.c

style:
	clang-format -n ./*/*/*.c ./*/*.c

style_red:
	clang-format -i ./*/*/*.c ./*/*.c

#valgrind
test_val: $(TETRIS_LIB)
	$(CC) $(FLAGS) $(FILETEST) $(TETRIS_LIB) -o $(FILETESTO) $(TESTFLAGS) $(FLAGCUR)
	valgrind --tool=memcheck --leak-check=yes \
	--track-origins=yes -s ./$(FILETESTO)
