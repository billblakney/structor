#include <cstdio>

extern void lex_main(char *aHeaderFile);

int main(int argc,char **argv)
{
   if( argc < 2 )
      printf("Usage: pp <in_file>\n");

  lex_main(argv[1]);
}
