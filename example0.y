%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
using namespace std;

extern int yylex();
extern void yyerror(char *);

#include "StructorUtil.hh"
#include "Structure.hh"
#include "Field.hh"

static StructorUtil u;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void pSummary()
{
   u.printSummary();
}

%}


%union {
   int     int_token;
   string* str_val;
}

%token <int_token> COMMA EQUALS LBRACE RBRACE SEMICOLON TYPEDEF ENUM STRUCT INT STAR
%token <str_val> NAME COMMENT

%start hfile

%%


// TODO For mem mgt, need to manage anything new-ed by the lex file.
// As of this writing, NAME is the only returned value that needs to be managed.

// Three elements are recognized in an "h" file:
// - enumeration declaration
// - structure definition
// - comment

hfile: /* empty */
     | hfile enum_decl
          {u.onMatch("hfile enum_decl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");}
     | hfile struct_decl
          {u.onMatch("hfile struct_decl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");}
     | hfile COMMENT
          {u.onMatch("comment\n");}

struct_decl: TYPEDEF STRUCT LBRACE member_list RBRACE NAME SEMICOLON
   {u.onStruct($6); delete $6;}

member_list: member
               {u.onMatch("member_list");}
             |
             member_list member
               {u.onMatch("member_list");}

member: NAME NAME SEMICOLON
           {u.onField($1,$2,0);}
        |
        NAME STAR NAME SEMICOLON
           {u.onField($1,$3,1);}

enum_decl: TYPEDEF ENUM NAME LBRACE enum_list RBRACE NAME SEMICOLON
   {u.onMatch("enum_decl");}

enum_list: last_enum_item
   {u.onMatch("last_enum_item 1");}
           |
           inner_enum_items last_enum_item
   {u.onMatch("last_enum_item 2");}

inner_enum_items: inner_enum_item
   {u.onMatch("inner_enum_item 1");}
           |
           inner_enum_items inner_enum_item
   {u.onMatch("inner_enum_item 2");}

inner_enum_item: NAME EQUALS INT COMMA
   {u.onMatch("inner_enum_item");}

last_enum_item: NAME EQUALS INT
   {u.onMatch("last_enum_item");}
