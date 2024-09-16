FLAGS = -Wall -Werror -Wextra

all : clean _cat

_cat :
	gcc $(FLAGS) _cat.c cat_func.c -o _cat

clean :
	rm -rf ./_cat

rebuild : clean all
