20131565 : main.o util.o lex.yy.o
	gcc -W -o 20131565 main.o util.o lex.yy.o
main.o : main.c globals.h
	gcc -W -c main.c
util.o : util.c util.h globals.h
	gcc -W -c util.c
lex.yy.o : lex.yy.c util.h globals.h
	gcc -W -c lex.yy.c
lex.yy.c : tiny.l
	flex tiny.l
clean:
	rm 20131565 main.o util.o lex.yy.o lex.yy.c
