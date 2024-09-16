FLAGS = -Wall -Werror -Wextra

all : clean _grep

_grep :
	gcc $(FLAGS) _grep.c grep_func.c -o _grep

clean :
	rm -rf ./_grep
	rm -rf ./test

build_san :
	gcc $(FLAGS) _grep.c grep_func.c -o _grep -fsanitize=address

rebuild : clean all