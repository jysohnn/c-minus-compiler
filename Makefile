cminus : main.o util.o lex.yy.o cm.tab.o analyze.o symtab.o code.o cgen.o
	gcc -W -o cminus main.o util.o lex.yy.o cm.tab.o analyze.o symtab.o code.o cgen.o
main.o : main.c lex.yy.c cm.tab.c cm.tab.h globals.h
	gcc -W -c main.c
util.o : util.c util.h lex.yy.c cm.tab.c cm.tab.h globals.h
	gcc -W -c util.c
lex.yy.o : lex.yy.c cm.tab.c cm.tab.h globals.h
	gcc -W -c lex.yy.c
lex.yy.c : cm.l cm.tab.c cm.tab.h globals.h
	flex cm.l
cm.tab.o : cm.tab.c cm.tab.h globals.h
	gcc -W -c cm.tab.c
cm.tab.c cm.tab.h : cm.y globals.h
	bison -d -v cm.y
analyze.o : analyze.c analyze.h cm.tab.c cm.tab.h globals.h
	gcc -W -c analyze.c
symtab.o : symtab.c symtab.h cm.tab.c cm.tab.h globals.h
	gcc -W -c symtab.c
code.o : code.c code.h cm.tab.c cm.tab.h globals.h
	gcc -W -c code.c
cgen.o : cgen.c cgen.h cm.tab.c cm.tab.h globals.h
	gcc -W -c cgen.c
clean:
	rm cminus main.o util.o lex.yy.o lex.yy.c cm.tab.o cm.tab.c cm.tab.h cm.output analyze.o symtab.o code.o cgen.o