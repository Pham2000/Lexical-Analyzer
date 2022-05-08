/***************************************************************
  Name: Tri Pham
  File Name: lexer.h

  Most important part of the project, by going through the lexer
  the program is able to get idLex and numLex which can be used
  in registers and postfix.
***************************************************************/

#ifndef LEXER_H
#define LEXER_H

#include "symbol.h"

#define MAX 20

//two character array or token that will be used throughout the program
char idLex[MAX];
char numLex[MAX];

//The files and filename to input
char* filename;
FILE * fp;
char ch;

//The line numbers and lookahead
int nPos;
int idPos;
int lineNo;
int lookahead;

//define the lexer
void initLexer(char* args);

//Perform lexical analyzing
int Lexan();

//Generate error messages
void error(int g);
#endif
