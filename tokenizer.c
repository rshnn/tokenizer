/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
	char* type;
	char* token;
	char* inputCopy;

	int parsingIndex;
	char currChar;
	int runningSize;
	int opFound;
};
typedef struct TokenizerT_ TokenizerT;















/* 
	Skipped items:  .  +  - for states 3, 9, and 12.
*/
int isOpCharTrunc(char c){

	switch(c){
		case '(': return 1;
		case ')': return 1;
		case '[': return 1;
		case ']': return 1;
		case '>': return 1;
		case '*': return 1;
		case '&': return 1;
		case '!': return 1;
		case '~': return 1;
		case '/': return 1;
		case '%': return 1;
		case '<': return 1;
		case '=': return 1;
		case '^': return 1;
		case '|': return 1;
		case ',': return 1;

		default: return 0;
	}

}

int isOpChar(char c){
	switch(c){
		case '(': return 1;
		case ')': return 1;
		case '[': return 1;
		case ']': return 1;
		case '>': return 1;
		case '*': return 1;
		case '&': return 1;
		case '!': return 1;
		case '~': return 1;
		case '/': return 1;
		case '%': return 1;
		case '<': return 1;
		case '=': return 1;
		case '^': return 1;
		case '|': return 1;
		case ',': return 1;
		
		case '.': return 1;
		case '+': return 1;
		case '-': return 1;

		default: return 0;	
	}
}



char nextChar(TokenizerT* tk){

	/* Exit fsm case:  Found delimeter or reached eof. */
	if(isspace(tk->inputCopy[tk->parsingIndex+1]) || tk->parsingIndex == strlen(tk->inputCopy)-1){

		tk->parsingIndex++;
		tk->currChar = tk->inputCopy[tk->parsingIndex];
		printf("END: curChar: '%c', Runningsize: %i, ParsingIndex: %i\n",tk->currChar, tk->runningSize, tk->parsingIndex);
		return 1;

	}

	/* Go to next character in input string. */
	else{

		tk->parsingIndex++;
		tk->currChar = tk->inputCopy[tk->parsingIndex];
		tk->runningSize++;

		printf("curChar: %c, Runningsize: %i\tParsingIndex: %i\n",tk->currChar, tk->runningSize, tk->parsingIndex);

		return tk->inputCopy[tk->parsingIndex];
	}

}

/* 
	Helper function for fsm to identify a digit in the range 0-7. 
	Returns 0 if false.
*/
int isOctal(char x){
	if(isdigit(x)){
		if(x == '8' || x == '9')
			return 0;
		else
			return 1;
	}
	return 0;
}
















/* C Operator stuff */
char state15(TokenizerT* tk){
	tk->opFound		= 1;
	tk->currChar 	= nextChar(tk);


	if(isOpChar(tk->currChar))
		return state15(tk);
	if(tk->currChar == 1)
		return 'c';

	else
		return 'c';

}





char state14(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state14(tk);
	if(tk->currChar == 1)
		return 'f';
	else
		return 'm';
}



char state13(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state14(tk);
	else
		return 'm';

}



char state12(TokenizerT* tk){
	tk->currChar = nextChar(tk);


	if(tk->currChar == '+' || tk->currChar == '-')
		return state13(tk);
	if(isdigit(tk->currChar))
		return state12(tk);
	else
		return 'm';

}





char state11(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state11(tk);
	if(tk->currChar == 1)
		return 'f';
	if(tk->currChar == 'E' || tk->currChar == 'e')
		return state12(tk);
	else
		return 'm';

}





char state10(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state11(tk);
	else
		return 'm';

}




char state9(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state9(tk);
	if(tk->currChar == '.')
		return state10(tk);
	if(tk->currChar == 1)
		return 'i';
	if(tk->currChar == 'E' || tk->currChar == 'e')
		return state12(tk);
	else
		return 'm';
}





char state8(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state8(tk);
	if(tk->currChar == 1)
		return 'f';
	if(tk->currChar == 'E' || tk->currChar == 'e')
		return state12(tk);
	else
		return 'm';
}



char state7(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isdigit(tk->currChar))
		return state8(tk);
	else
		return 'm';
}



char state6(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isxdigit(tk->currChar))
		return state6(tk);
	if(tk->currChar == 1)
		return 'h';
	else
		return 'm';
}



char state5(TokenizerT* tk){
	tk->currChar = nextChar(tk);
	//printf("\tIn state 5\n");


	if(isxdigit(tk->currChar))
		return state6(tk);
	else
		return 'm';
}






char state4(TokenizerT* tk){
	tk->currChar = nextChar(tk);
	//printf("\tIn state 4\n");



	if(isOctal(tk->currChar))
		return state4(tk);
	if(tk->currChar == 1)
		return 'o';
	else
		return 'm';
}









char state3(TokenizerT* tk){
	tk->currChar = nextChar(tk);
	//printf("\tIn state 3\n");



	if(isOctal(tk->currChar)){
		return state4(tk);
	}
	if(tk->currChar == 'x' || tk->currChar == 'X'){
		return state5(tk);
	}
	if(tk->currChar == '.'){
		return state7(tk);
	}
	if(tk->currChar == 1){
		return 'z';
	}else{
		return 'm';
	}

}



char state2(TokenizerT* tk){
	//tk->currChar = nextChar(tk);
	//printf("\tIn state 2\n");


	if(tk->currChar == 1)
		return 'i';
	if(isdigit(tk->currChar)){
		if(tk->currChar == '0'){
			return state3(tk);
		}else
			return state9(tk);
	}
	else
		return 'm';

}



char state1(TokenizerT* tk){
	tk->currChar = nextChar(tk);
	//printf("\tIn state 1\n");


	if(tk->currChar == 1)
		return 'w';
	if(isalnum(tk->currChar))
		return state1(tk);
	if(isOpChar(tk->currChar)){
		tk->opFound = 1;
		return 'w';
	}
	else
		return 'm';
}





char state0(TokenizerT* tk){
	tk->currChar = nextChar(tk);

	if(isOpChar(tk->currChar)){
		return state15(tk);
	}
	if(isalpha(tk->currChar))
		return state1(tk);
	if(isdigit(tk->currChar))
		return state2(tk);

	else
		return 'm';
}






/*
	runFSM will initiate the finite state machine interpreter.
	The function call will return 0 if a token is successfully created
		and will return 1 if eof is reached.
*/

int runFSM(TokenizerT* tk){

	printf("\n\nStarting FSM\nParsingIndex: %i\n", tk->parsingIndex);

	/* If eof reached */
	if(tk->parsingIndex == strlen(tk->inputCopy)){
		printf("At eof\n");
		return 1;
	}



	char 	type 	= 0;
	char*	output	= 0; 

	type 	= state0(tk);


	switch (type){
		case 'm': output 	= "malformed"; break;
		case 'i': output 	= "integer"; break;
		case 'w': output 	= "word"; break;
		case 'h': output	= "hex constant"; break;
		case 'o': output 	= "octal constant"; break;
		case 'z': output	= "zero"; break;
		case 'f': output 	= "float"; break;
		case 'c': output	= "C op"; break;
		default: output 	= "idunno"; break;

	}


	tk->type = output;

	printf("\nDONE WITH TOK: %s - ParsingIndex: %i - RunningSize: %i\n",output,tk->parsingIndex, tk->runningSize);
	return 0;
}

































































/* 
	This function will print the information of a token in standard output for debugging purposes.
*/
void printToken1(TokenizerT* ts){

	printf("\n\n\t-------------PRINTING\n\t The full input: '%s'\n", ts->inputCopy);
	printf("\t The token is: '%s' of length %lu and of type: '%s' %lu\n",ts->token, strlen(ts->token), ts->type, strlen(ts->type));
	printf("\t The parsing index is ( %i )\n", ts->parsingIndex);
	printf("\t---------------------------------\n\n");
	

}

/*
	This function will print the type of the token and the token in stdout.
*/
void printToken(TokenizerT* tk){

	if(tk->token != 0 && tk->type != 0)
		printf("\t\t\t\t\t\t\t\t%s \"%s\"\n",tk->type, tk->token);

}










/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

	/* Local, temp variable declarations. */
	char* 	tokenBuffer 	= 	0;
	TokenizerT*	tokenizer 	= 	(TokenizerT*)malloc(sizeof(TokenizerT));

	/* Finding heap space for the token. */
	tokenBuffer = (char*)malloc(sizeof(char)*1);
	if(tokenBuffer == NULL){
		free(tokenBuffer);
		return NULL;
	}

	/* Intializing tokenizer structure. */
	tokenizer->inputCopy 	= ts;
	tokenizer->token 		= tokenBuffer;
	tokenizer->type 		= 0;
	tokenizer->parsingIndex = -1;
	tokenizer->currChar		= 0;
	tokenizer->runningSize	= 0;
	tokenizer->opFound		= 0;
	printf("The tokenizer was initialized.\n");


	return tokenizer;
}

/*
 * TKDestroy destroys a TokenizerT object.  It sho2uld free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */
void TKDestroy( TokenizerT * tk ) {
	//free(tk->type);
	free(tk->token);
	free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

	if(runFSM(tk) == 0){
		int size 		= 0;
		int startAddr	= 0;

		

		if(tk->runningSize != 0){			
			
			/* Dynamic allocation for token */
			size 		= tk->runningSize;
			tk->token 	= (char*)realloc(tk->token,(size+1));
			startAddr	= tk->parsingIndex-size;

			printf("\nOP found status: %i\n",tk->opFound);

			if(strcmp(tk->type,"malformed") == 0)
				startAddr++;

				
			memcpy(tk->token, &tk->inputCopy[startAddr],size);
			tk->token[size] = '\0';

			tk->opFound		= 0;
			tk->runningSize = 0;
		}else{
			tk->token = 0;
			tk->type = 0;
			tk->opFound = 0;
		}

		return tk->token;
	}
  	return 0;
}






/* 
	Agument validity checking.  Includes -help option. 
*/
void argCheck(int argc, char** argv){

	char* argNumErr = "Incorrect number of arguments given.  Use \"tokenizer -help\" for proper usage infomation.\n";  
	switch(argc){
		case 2:
			if ( strcmp(argv[1], "-help")== 0 ){
				fprintf(stderr, "\nProper usage:  ./tokenizer \"argument to tokenize may include 0x3284\"\n\n");
				exit(0);
			}
			break;
	
		default: 
			fprintf(stderr, "%s\n", argNumErr);
			exit(0);
	}
	printf("Passed initial arguments test. \n");
}





/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	
	/* Argument validity check.  Include -help option */
	argCheck(argc, argv);
	TokenizerT* tokenizer = TKCreate(argv[1]);



	while(TKGetNextToken(tokenizer) != 0){

		printToken1(tokenizer);
		printToken(tokenizer);

	}










	/*  PROGRESS NOTES TO SELF:;

	*/


	TKDestroy(tokenizer);
  	return 0;
}














