flags = -Wall -Werror -Wextra

all: s21_cat

rebuild: clean all

s21_cat: cat_flags.o cat_for_table.o cat_open.o cat_parse.o cat_for_read.o cat.o
	gcc $(flags) cat_flags.o cat_for_table.o cat_open.o cat_parse.o cat_for_read.o cat.o -o s21_cat

cat.o: cat.c
	gcc $(flags) -c cat.c -o cat.o

cat_flags.o: cat_flags.c
	gcc $(flags) -c cat_flags.c -o cat_flags.o

cat_for_table.o: cat_for_table.c
	gcc $(flags) -c cat_for_table.c -o cat_for_table.o

cat_parse.o: cat_parse.c
	gcc $(flags) -c cat_parse.c -o cat_parse.o

cat_open.o: cat_open.c
	gcc $(flags) -c cat_open.c -o cat_open.o

cat_for_read.o: cat_for_read.c
	gcc $(flags) -c cat_for_read.c -o cat_for_read.o

clean:
	rm -rf *.o
	rm -rf s21_cat