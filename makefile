MY_ENV =

ifeq ($(MY_ENV),CYGWIN)
INCLUDES = -I./include -IC:/tools/cygwin64/usr/include
INCLUDES = -I./include -I/cygdrive/c/tools/cygwin64/usr/i686-pc-mingw32/sys-root/mingw/include
endif

LIBS = -llog4cxx -lboost_regex
LIBS = -lboost_regex

EXE = structor
 
CC = g++
# To avoid missing 'fileno', need to use gnu+11 instead of c+11
#CFLAGS = -g -std=c++11 $(INCLUDES)
#CFLAGS = -g -std=gnu++11 $(INCLUDES)
CFLAGS = -g $(INCLUDES)

all : parser lexer structorutil field structure main
	$(CC) $(CFLAGS) -o $(EXE) lex.yy.c example0.tab.c StructorUtil.o Field.o Structure.o main.o

 
lexer : example0.l
	flex example0.l
 
parser : example0.y
	bison -d example0.y

structure: Structure.cc Structure.hh
	$(CC) $(CFLAGS) -c Structure.cc

main: main.cc
	$(CC) $(CFLAGS) -c main.cc

field: Field.cc Field.hh
	$(CC) $(CFLAGS) -c Field.cc

structorutil: StructorUtil.cc StructorUtil.hh
	$(CC) $(CFLAGS) -c StructorUtil.cc

clean :
	rm -f *.o example0.tab.c example0.tab.h lex.yy.c $(EXE)
