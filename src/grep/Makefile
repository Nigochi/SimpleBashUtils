flags = -Wall -Werror -Wextra

all: s21_grep

rebuild: clean all

s21_grep: s21_grep.o grep_flags.o grep_parse_distribute.o grep_helpers.o grep_free.o grep_open.o grep_to_decide.o
	gcc $(flags) s21_grep.o grep_flags.o grep_helpers.o grep_parse_distribute.o grep_free.o grep_to_decide.o grep_open.o -o s21_grep

s21_grep.o: s21_grep.c
	gcc $(flags) -c s21_grep.c -o s21_grep.o

grep_parse_distribute.o: grep_parse_distribute.c
	gcc $(flags) -c grep_parse_distribute.c -o grep_parse_distribute.o

grep_helpers.o: grep_helpers.c
	gcc $(flags) -c grep_helpers.c -o grep_helpers.o

grep_flags.o: grep_flags.c
	gcc $(flags) -c grep_flags.c -o grep_flags.o

grep_free.o: grep_free.c
	gcc $(flags) -c grep_free.c -o grep_free.o

grep_to_decide.o: grep_to_decide.c
	gcc $(flags) -c grep_to_decide.c -o grep_to_decide.o

grep_open.o: grep_open.c
	gcc $(flags) -c grep_open.c -o grep_open.o

clean:
	rm -rf *.o
	rm -rf s21_grep