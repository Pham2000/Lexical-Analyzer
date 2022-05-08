/***************************************************************
  Name: Tri Pham
  File Name: symbol.h

  Symbol table that is meant to store postfix, able to return
  found and not found if lookup an item.
***************************************************************/

#ifndef SYMBOL_H
#define SYMBOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Define all sort of numbers that will be used from getting tokens to generating errors
#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401
#define NEWID 302 
#define NOT_FOUND -1
#define FOUND -2
#define REDEF 619
#define MAXTABLE 100
#define MAXCHAR 10
#define DONE 0

//Increment of the table
int tableInt;

//The table itself
char table[MAXTABLE][MAXCHAR];

//Initialize the table, not really but it work
void initSymbol();

//insert into table
void insert(char* word);

//lookup show what found and not found
int lookup(char* word);

#endif
