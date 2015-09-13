%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

extern int yylex();
extern void yyerror(char *);

#include "StructorUtil.hh"
#include "Structure.hh"
#include "Field.hh"

vector<Structure *> structs;

static StructorUtil util;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void pMatch(const char *aRuleName)
{
   static int _debug = 0;
   if( _debug )
      printf("matched: %s\n",aRuleName);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void pField(string *aName,string *aType,int aIsPointer)
{
   static int _debug = 0;
   Field tField(*aName,*aType,aIsPointer);
   util.addField(tField);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void pStruct(std::string *aStructName)
{
   static int _debug = 0;

   Structure *tStructure = new Structure(*aStructName);
   delete aStructName;
   
   structs.push_back(tStructure);
   if( _debug )
      printf("struct: %s\n",tStructure->_Name.c_str());

   util.printFields();
   util.clearFields();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void pSummary()
{
   static int _debug = 1;
   vector<Structure *>::iterator it;
   for( it = structs.begin() ; it != structs.end(); it++ ){
      printf("struct: %s\n",(*it)->_Name.c_str());
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


// TODO For mem mgt, need to manage anything new-ed by the lex file.
// As of this writing, NAME is the only returned value that needs to be managed.

// Three elements are recognized in an "h" file:
// - enumeration declaration
// - structure definition
// - comment

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
           {pField($1,$2,0);}
        |
        NAME STAR NAME SEMICOLON
           {pField($1,$3,1);}

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
