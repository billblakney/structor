######################################################################
# Automatically generated by qmake (2.00a) Thu Sep 7 15:54:07 2006
######################################################################
 
#TEMPLATE = app
TEMPLATE = lib
TARGET = structor.o
DEPENDPATH += .
INCLUDEPATH += .

QMAKE_CXX = g++
QMAKE_CC = g++
 
# Input
HEADERS += Field.hh StructorBuilder.hh Structure.hh
#LEXSOURCES += parser.l
#YACCSOURCES += parser.y
SOURCES += main.cc Field.cc StructorBuilder.cc Structure.cc

LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_regex
 
# Flex/bison specifics
 
#QMAKE_LEX = flex
#QMAKE_YACC = bison
 
#QMAKE_YACCFLAGS = -d -o y.tab.c
#QMAKE_YACC_HEADER =
#QMAKE_YACC_SOURCE =
 
FLEXSOURCES = parser.l
BISONSOURCES = parser.y
 
flex.commands = flex ${QMAKE_FILE_IN}
flex.input = FLEXSOURCES
flex.output = lex.yy.c
flex.variable_out = SOURCES
flex.depends = y.tab.h
flex.name = flex
QMAKE_EXTRA_COMPILERS += flex
 
bison.commands = bison -d -t -y ${QMAKE_FILE_IN} && mv y.tab.c y.tab.cpp
bison.input = BISONSOURCES
bison.output = y.tab.cpp
bison.variable_out = SOURCES
bison.name = bison
QMAKE_EXTRA_COMPILERS += bison
 
bisonheader.commands = @true
bisonheader.input = BISONSOURCES
bisonheader.output = y.tab.h
bisonheader.variable_out = HEADERS
bisonheader.name = bison header
bisonheader.depends = y.tab.cpp
QMAKE_EXTRA_COMPILERS += bisonheader
