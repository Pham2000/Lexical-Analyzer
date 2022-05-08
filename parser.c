/***************************************************************
  Name: Tri Pham
  File Name: parser.c

  define parser.h file, and add a way for the code to be store
  and written to a file, while also passing errors of item that
  is not correct.
***************************************************************/

#include "parser.h"

//look through the line of text more in depth
void AssignStmt(){
	
	//if what follow int follow by commas, we look for ; and put the variable in table
	while(lookahead == ','){
		match(',');
		match(ID);
		finding();
	}
	if(lookahead == ';')
		match(';');
	
	//while new int we keep look through and put it in table
	while(lookahead == NEWID){
		match(NEWID);
		match(ID);
		finding();
		while(lookahead == ','){
			match(',');
			match(ID);	
			finding();
		}
		match(';');
	}
	
	//look at the current ID, to find variable defined
	match(ID);
	strcpy(variable, idLex); // put it in variable to be used to generate files
	
	starter = 0; //for register
	iT = 0;	//Initializer for postfix
	
	if(lookahead != '=')
		error('=');
	
	// look through the line definition
	else{
		initSymbol();
		match(lookahead);
		expression();
		match(';');
	}
	
	//message to be used to generate out file
	strcat(fileInput, statement);
	if(strcmp(r0, "") != 0){
		strcat(fileInput, "R0 = ");
		strcat(fileInput, r0);
		strcat(fileInput, "\n");
	}
	strcat(fileInput, variable);
	strcat(fileInput, " = R0");

	strcat(fileInput, "\n****[");
	for(int i = 0; i < iT; i++){
		strcat(fileInput, table[i]);
		if(i < iT - 1){
			strcat(fileInput, ", ");
		}
	}
	strcat(fileInput, "]****\n");
	strcpy(r0, "");
	strcpy(r1, "");
	strcpy(r2, "");
	strcpy(statement, "");
	strcpy(variable, "");
}

// Look through the register to know where in postfix we are
//addition and minus of the variables
void expression(){
	term();
	while(lookahead == '+' || lookahead == '-'){
		if(starter == 0 && strcmp(r0, "") != 0){ //assign register 0
                	strcat(statement, "R0 = ");
                	strcat(statement, r0);
                	strcat(statement, "\n");
                	strcpy(r0, "");
                	starter = 1; //switch to register 1
        	}
        	else if(starter == 1 && strcmp(r1, "") != 0){ // assign register 1
                	strcat(statement, "R1 = ");
                	strcat(statement, r1);
                	strcat(statement, "\n");
                	strcpy(r1, "");
                	starter = 2; //switch to register 2
        	}

		int temp = lookahead; //operator = lookahead
		match(lookahead);
		term();
		char* c;
		//put the operator into the statement
                if(temp == '+'){
                        insert("+");
			c = "+";
			++iT;
		}
                else{
                        insert("-");
			c = "-";
			++iT;
		}
		//if it register 1, then we put print out the Register operation
		if(starter == 1){
			if(strcmp(r1, "") != 0){	
				strcat(statement, "R1 = ");
				strcat(statement, r1);
				strcat(statement, "\n");
				strcpy(r1, "");
			}

			strcat(statement, "R0 = R0 ");
                        strcat(statement, c);
                        strcat(statement, " R1");
			strcat(statement, "\n");
		}
		//do the same thing here
		else if(starter == 2){
			if(strcmp(r2, "") != 0){
				strcat(statement, "R2 = ");
                        	strcat(statement, r2);
				strcat(statement, "\n");
				strcpy(r2, "");
			}
			else{
				starter = 1;
			}
                        strcat(statement, "R1 = R1 ");
                        strcat(statement, c);
                        strcat(statement, " R2");
			strcat(statement, "\n");
		}

		
	}
}
//multiplication and division of variable
void term(){
	factor();
	while(lookahead == '*' || lookahead == '/'){
		if(starter == 0 && strcmp(r0, "") != 0){ //assign register 0
                        strcat(statement, "R0 = ");
                        strcat(statement, r0);
                        strcat(statement, "\n");
                        strcpy(r0, "");
                        starter = 1; //switch to register 1
                }
                else if(starter == 1 && strcmp(r1, "") != 0){ // assign register 1
                        strcat(statement, "R1 = ");
                        strcat(statement, r1);
                        strcat(statement, "\n");
                        strcpy(r1, "");
                        starter = 2; //switch to register 2
                }

		int temp = lookahead; //operator = lookahead
		match(lookahead);
		factor();
		char* c;
		//put the operator into the statement
		if(temp == '*'){
			insert("*");
			c = "*";
			++iT;
		}
		else{
			insert("/");
			c = "/";
			++iT;
		}
        //if it register 1, then we put print out the Register operation        
		if(starter == 1){
                        if(strcmp(r1, "") != 0){
                                strcat(statement, "R1 = ");
                                strcat(statement, r1);
				strcat(statement, "\n");
                                strcpy(r1, "");
                        }
			strcat(statement, "R0 = R0 ");
                        strcat(statement, c);
                       	strcat(statement, " R1");
                        strcat(statement, "\n");

                }
				//do the same here
                else if(starter == 2){
                        if(strcmp(r2, "") != 0){
                                strcat(statement, "R2 = ");
                                strcat(statement, r2);
				strcat(statement, "\n");
                                strcpy(r2, "");
                        }
			else{
				starter = 1;
			}
			strcat(statement, "R1 = R1 ");
                        strcat(statement, c);
                        strcat(statement, " R2");
                        strcat(statement, "\n"); 
                }
	}
}
//assign the IdLex to the correct register to be printed
void factor(){
	if(lookahead == ID){
		match(ID);
		insert(idLex);
		++iT;
		
		if(starter == 0){
			strcpy(r0, "");
			strcat(r0, idLex);
		}
		else if(starter == 1){			                        
			strcpy(r1, "");
                        strcat(r1, idLex);
		}
		else if(starter == 2){
			strcpy(r2, "");
			strcat(r2, idLex);		
		}
	}
	else if(lookahead == NUM){
		match(NUM);
		insert(numLex);
		++iT;

                if(starter == 0){
                        strcpy(r0, "");
                        strcat(r0, numLex);
                }
                else if(starter == 1){
                        strcpy(r1, "");
                        strcat(r1, numLex);
                }
                else if(starter == 2){
                        strcpy(r2, "");
                        strcat(r2, numLex);
                }

	}
	else if(lookahead == '('){
		match('(');
		expression();
		match(')');
		if(starter == 2){
			starter = 1;
		}
	}
}

//If not match there an error
void match(int t){
	if(lookahead == t){
		lookahead = Lexan();
	}
	else{
		error(t);	
	}
}		

//parse the beginning of textfile to the end
void parse(){
	match(BEGIN);
	match(NEWID);
	match(ID);
	finding();
	while(lookahead != END)
		AssignStmt();
	match(END);
	match('.');
	printf("The program is legal output is in file");
	char* filer = gettingFileName();
	printf(" \"%s\"", filer);
        fp = fopen(filer, "w");
	
	fprintf(fp, "Compiling %s\n", filename);
	printf("\n%s\n", fileInput);
	fprintf(fp, fileInput);
	fclose(fp);	
}
//inserting into the symboltable
void finding(){
		int type = lookup(idLex);
		if(type == NOT_FOUND)
			insert(idLex);
		else if(type == FOUND)
			error(REDEF);
}

//filename generator
char* gettingFileName(){
	int l = strlen(filename);
	char* word = malloc(l+1);
	for(int i = 0; i <= l; i++){
		word[i] = filename[i];
	}
	word[l] = 't';
	word[l-1] = 'u';
	word[l-2] = 'o';
	return word;

}
