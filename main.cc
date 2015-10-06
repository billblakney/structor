#include <cstdio>
#include "StructorUtil.hh"

extern StructorUtil &lex_main(char *aHeaderFile);

int main(int argc,char **argv)
{
   if( argc < 2 )
      printf("Usage: pp <in_file>\n");

   StructorUtil &util = lex_main(argv[1]);
   util.printSummary();
   util.postProcess();
}
