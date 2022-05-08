/***************************************************************
  Name: Tri Pham
  File Name: symbol.c

  Define functions of file symbol.h for everything to work 
  correctly.
***************************************************************/

#include "symbol.h"

//Look up if word is in symbol table or not
int lookup(char* word){
	for(int i = 0; i < MAXTABLE; i++){
		if(strcmp(table[i], word) == 0){
			return FOUND;
		}
	}
	return NOT_FOUND;	
}

//insert the word into the symbol table
void insert(char* word){
	strcpy(table[tableInt], "");
	strcpy(table[tableInt], word);
	tableInt++;
}

//make all space in table empty
void initSymbol(){
	tableInt = 0;
	for(int i = 0; i < MAXTABLE; i++){
		strcpy(table[tableInt], "");
	}

}	
