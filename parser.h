/***************************************************************
  Name: Tri Pham
  File Name: parse.h

  Parser that do semantic check, generate a file of Register and
  postfix. 
***************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "string.h"
#define STRLENGTH 50
#define FILELENGTH 2000

//text to be input into outfile
char fileInput[FILELENGTH];

//store the many statement that will be used to generate outfiles
char statement[FILELENGTH];

char variable[STRLENGTH];

//register
char r0[STRLENGTH];

char r1[STRLENGTH];

char r2[STRLENGTH];

//which register
int starter;

//postfix initializers
int iT;

FILE *f;

//Look at the line of code
void AssignStmt();

//look for the + -
void expression();

//look for * /
void term();

//store the id and num
void factor();

//match the lookahead
void match(int t);

//look through the whole file
void parse();

//inserting to symbol table
void finding();

//generating outfile names
char* gettingFileName();

#endif
