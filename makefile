MY_ENV =

ifeq ($(MY_ENV),CYGWIN)
INCLUDES = -I./include -IC:/tools/cygwin64/usr/include
INCLUDES = -I./include -I/cygdrive/c/tools/cygwin64/usr/i686-pc-mingw32/sys-root/mingw/include
endif

#LIBS = -llog4cxx -lboost_regex -lboost
LIBS = -L/usr/lib/x86_64-linux-gnu -lboost_regex
#LIBS = -lboost_regex

EXE = structor
ALIB = structor.so

CC = g++
# To avoid missing 'fileno', need to use gnu+11 instead of c+11
#CFLAGS = -g -std=c++11 $(INCLUDES)
#CFLAGS = -g -std=gnu++11 $(INCLUDES)
CFLAGS = -g $(INCLUDES) -fPIC

LDFLAGS = -shared

all : parserlexer structorutil field structure main
	$(CC) $(CFLAGS) -o $(ALIB) lex.yy.o example0.tab.o StructorBuilder.o Field.o Structure.o main.o $(LIBS) $(LDFLAGS)
#	$(CC) $(CFLAGS) -o $(EXE) lex.yy.o example0.tab.o StructorBuilder.o Field.o Structure.o main.o $(LIBS)

#	$(CC) $(CFLAGS) lex.yy.c example0.tab.c
# 	$(CC) $(CFLAGS) -Os -fPIC -c StructorBuilder.o Field.o Structure.o main.o
#	$(CC) $(CFLAGS) -shared $(ALIB) lex.yy.c example0.tab.c StructorBuilder.o Field.o Structure.o main.o $(LIBS)

parserlexer : parser lexer
	$(CC) $(CFLAGS) -c lex.yy.c example0.tab.c
 
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

structorutil: StructorBuilder.cc StructorBuilder.hh
	$(CC) $(CFLAGS) -c StructorBuilder.cc

clean :
	rm -f *.o example0.tab.c example0.tab.h lex.yy.c $(EXE)
