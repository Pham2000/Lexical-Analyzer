/***************************************************************
  Name: Tri Pham
  File Name: lexer.c

  define lexer.h file and have a running lexan and error messages
  to be used in the other program.
***************************************************************/

#include "lexer.h"

//define all the variables needed
void initLexer(char* args){
	filename = args;
	fp = fopen(filename, "r");
	nPos = 0;
	idPos = 0;
	lineNo = 1;
	lookahead = Lexan();
}

//Lexical analyzer that skip space, tabs, comments, and newlines
int Lexan(){
	while((ch = fgetc(fp)) != EOF){
        	if(ch == ' ' || ch == '\t');
        	else if(ch == '\n'){
            		lineNo++;
		}
        	else if(ch == '~'){
         		while(ch != '\n'){
                		ch = fgetc(fp);
			}
			ungetc(ch,fp);
	        }
        	else if(isdigit(ch)){
			memset(numLex, 0, MAX);
			numLex[0] = ch;
			nPos = 1;
			ch = fgetc(fp);
			while(isdigit(ch)){
				numLex[nPos++] = ch;
				ch = fgetc(fp);
			}
			ungetc(ch, fp);
			numLex[nPos] = '\0';
            		return NUM;
        	}
        	else if(isalpha(ch)){
			memset(idLex, 0, MAX);
			idLex[0] = ch;
			idPos = 1;
			ch = fgetc(fp);
			while(isalpha(ch) || isdigit(ch) || ch == '_'){
				//check for consecutive _
				if(idLex[idPos] == '_' && ch == '_'){
					error('_' + '_');
				}
            			idLex[idPos++] = ch;
				ch = fgetc(fp);
			}
			//check for ending with _
			if(idLex[idPos-1] == '_')
				error('_');
			ungetc(ch,fp);
			idLex[idPos] = '\0';
			
			//symbol tables not needed here since the parser will be using it for postfix
			if(strcmp(idLex, "begin") == 0){
				return BEGIN;
			}
			else if(strcmp(idLex, "end") == 0){
				return END;
			}
			else if(strcmp(idLex, "int") == 0){
				return NEWID;
			}	
			else{
				return ID;
			}

        	}
		else{
			return ch;
		}
	}
	return DONE;
	fclose(fp);	

}

//Generate messages through the define variables
void error(int g){
	if(g == '_')
		fprintf(stderr, "Syntax Error line %d: variable %s can't end with '%c'\n", lineNo, idLex, g);
	
	else if(g == '_'+'_')
		fprintf(stderr, "Syntax Error line %d: varible %s can't have consecutive '%c'\n", lineNo, idLex, g);
	
	else if(g == '*' || g == '+' || g == '-' || g == '/' || g == '=' || g == ')' || g == '(' || g == ';')
        	fprintf(stderr, "Syntax Error line %d: variable %s missing '%c'\n", lineNo, idLex, g);
	
	else if(g == BEGIN)
		fprintf(stderr, "Error line %d: missing 'BEGIN'\n", lineNo);
	
	else if(g == END)
		fprintf(stderr, "Error line %d: missing 'END'\n", lineNo);
	
	else if(g == NEWID)
		fprintf(stderr, "Error line %d: variable %s is undefined\n", lineNo, idLex);

	else if(g == REDEF)
		fprintf(stderr, "Error line %d: variable %s is redefined\n", lineNo, idLex);			
        
	exit(EXIT_FAILURE);
}

