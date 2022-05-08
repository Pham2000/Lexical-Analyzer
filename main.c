/***************************************************************
  Name: Tri Pham
  File Name: main.c

  Put the filename into lexer, initialize symbol table, start
  the parser and run the program.
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "lexer.h"
#include "parser.h"
int main(int argc, char *argv[]){
	//pass the filename into lexer
	initLexer(argv[1]);
	initSymbol();
	printf("\n\nCompiling %s\n", argv[1]);
	parse();
	return 0;
}
