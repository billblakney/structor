%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

extern int yylex();
extern void yyerror(char *);

vector<string> structs;

void pMatch(const char *aRuleName)
{
   static int _debug = 0;
   if( _debug )
      printf("matched: %s\n",aRuleName);
}

void pStruct(string *aStructName)
{
   static int _debug = 0;
   structs.push_back(*aStructName);
   if( _debug )
      printf("struct: %s\n",aStructName->c_str());
}

void pSummary()
{
   static int _debug = 1;
   for( vector<string>::iterator it = structs.begin() ; it != structs.end(); it++ ){
      printf("struct: %s\n",it->c_str());
   }
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

hfile: /* empty */
     | hfile enum_decl
          {pMatch("hfile enum_decl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");}
     | hfile struct_decl
          {pMatch("hfile struct_decl@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");}
     | hfile COMMENT
          {pMatch("comment\n");}

struct_decl: TYPEDEF STRUCT LBRACE member_list RBRACE NAME SEMICOLON
   {pStruct($6);}

member_list: member
               {pMatch("member_list");}
             |
             member_list member
               {pMatch("member_list");}

member: NAME NAME SEMICOLON
           {pMatch("member");}
        |
        NAME STAR NAME SEMICOLON
           {pMatch("pointer member");}

enum_decl: TYPEDEF ENUM NAME LBRACE enum_list RBRACE NAME SEMICOLON
   {pMatch("enum_decl");}

enum_list: last_enum_item
   {pMatch("last_enum_item 1");}
           |
           inner_enum_items last_enum_item
   {pMatch("last_enum_item 2");}

inner_enum_items: inner_enum_item
   {pMatch("inner_enum_item 1");}
           |
           inner_enum_items inner_enum_item
   {pMatch("inner_enum_item 2");}

inner_enum_item: NAME EQUALS INT COMMA
   {pMatch("inner_enum_item");}

last_enum_item: NAME EQUALS INT
   {pMatch("last_enum_item");}
