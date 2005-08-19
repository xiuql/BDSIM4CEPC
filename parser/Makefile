CC=g++
OBJ=gmad.o lex.yy.o parser.tab.o 
LIB=-lfl

LEX=flex
LOPT=-i

YACC=bison
YOPT=-d -v

# For Mac (Darwin)
DYFLAGS=-O2 -dynamiclib -undefined error

#parsing library

# For Linux
#libgmad.so : $(OBJ)
#	$(CC) -W1 -shared -g -o libgmad.so $(OBJ) $(LIB)

# For Mac (Darwin) - using dynamic libraries instead of shared
 libgmad.dylib : $(OBJ)
	$(CC) $(DYFLAGS) -o libgmad.dylib $(OBJ) $(LIB)

# gmad parser

parser : parser.cc gmad.h libgmad.so 
	$(CC) parser.cc -g -o parser -L. -lgmad


gmad.o :gmad.cc gmad.h
	$(CC) -Wall -fpic -g -c gmad.cc

lex.yy.o : lex.yy.c parser.tab.c parser.tab.h sym_table.h
	$(CC) -Wall -fpic -g -c  lex.yy.c

parser.tab.o : parser.tab.h parser.tab.c sym_table.h 
	$(CC) -Wall -fpic -g -c $(INCL)  parser.tab.c

lex.yy.c : parser.l parser.tab.h parser.y parser.h
	$(LEX) $(LOPT) parser.l

parser.tab.h parser.tab.c : parser.y parser.h
	$(YACC) $(YOPT) parser.y

clean :
	rm -f parser libgmad.so $(OBJ) lex.yy.c parser.tab.c parser.tab.h


# ggmad (geometry) parser

gparser : gparser.cc ggmad.hh libggmad.so 
	$(CC) gparser.cc -o gparser -L. -lggmad


ggmad.o :ggmad.cc
	$(CC) -Wall -fpic -c ggmad.cc

glex.yy.o : glex.yy.c gparser.tab.c gparser.tab.h sym_table.h
	$(CC) -Wall -fpic -c  lex.yy.c

gy.tab.o : gparser.tab.h gparser.tab.c sym_table.h 
	$(CC) -Wall -fpic -c $(INCL)  gparser.tab.c

lex.gg.c : gparser.l gparser.tab.h gparser.y 
	$(LEX) $(LOPT) -Pgg gparser.l

gparser.tab.h gparser.tab.c : gparser.y
	$(YACC) $(YOPT) gparser.y

