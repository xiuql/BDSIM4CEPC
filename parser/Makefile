CC=g++
OBJ=gmad.o lex.yy.o parser.tab.o
LIB=-lfl

LEX=flex
LOPT=-i

YACC=bison
YOPT=-d -v

parser : parser.cc gmad.h libgmad.so 
	$(CC) parser.cc -o parser -L. -lgmad

libgmad.so : $(OBJ)
	$(CC) -W1 -shared -o libgmad.so $(OBJ) $(LIB)

gmad.o :gmad.cc gmad.h
	$(CC) -Wall -fpic -c gmad.cc

lex.yy.o : lex.yy.c parser.tab.c parser.tab.h sym_table.h
	$(CC) -Wall -fpic -c  lex.yy.c

y.tab.o : parser.tab.h parser.tab.c sym_table.h 
	$(CC) -Wall -fpic -c $(INCL)  parser.tab.c

lex.yy.c : parser.l parser.tab.h parser.y parser.h
	$(LEX) $(LOPT) parser.l

parser.tab.h parser.tab.c : parser.y parser.h
	$(YACC) $(YOPT) parser.y

clean :
	rm -f parser libgmad.so $(OBJ) lex.yy.c parser.tab.c parser.tab.h
