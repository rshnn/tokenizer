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
};
typedef struct TokenizerT_ TokenizerT;























char nextChar(TokenizerT* tk){

	/* Exit fsm case:  Found delimeter or reached eof. */
	if(isspace(tk->inputCopy[tk->parsingIndex+1]) || tk->parsingIndex == strlen(tk->inputCopy)-1){

		printf("~Found a space or end of file.\n");
		tk->parsingIndex++;
		tk->currChar = tk->inputCopy[tk->parsingIndex];

		printf("curChar: %c, Runningsize: %i\n",tk->currChar, tk->runningSize);


		return 1;

	}
	else{

		tk->parsingIndex++;
		tk->currChar = tk->inputCopy[tk->parsingIndex];
		tk->runningSize++;

		printf("curChar: %c, Runningsize: %i\tParsingIndex: %i\n",tk->currChar, tk->runningSize, tk->parsingIndex);


		return tk->inputCopy[tk->parsingIndex];
	}

}








char state1(TokenizerT* tk){
	tk->currChar = nextChar(tk);



	if(tk->currChar == 1)
		return 'w';
	

	if(isalpha(tk->currChar))
		return state1(tk);
	

	else
		return 'm';
	

}




char state2(TokenizerT* tk){
	tk->currChar = nextChar(tk);


	if(tk->currChar == 1){
		return 'n';
	}
	if(isdigit(tk->currChar)){
		return state2(tk);
	}else
		return 'm';

}


char state0(TokenizerT* tk){
	tk->currChar = nextChar(tk);


	if(isalpha(tk->currChar)){
		return state1(tk);
	}

	if(isdigit(tk->currChar)){
		return state2(tk);
	}
	else{
		return 'm';
	}


}



/*
	runFSM will initiate the finite state machine interpreter.
	The function call will return 0 if a token is successfully created
		and will return 1 if eof is reached.
*/

int runFSM(TokenizerT* tk){

	/* If eof reached */
	if(tk->parsingIndex == strlen(tk->inputCopy)){
		printf("At eof\n");
		return 1;
	}


	//tk->currChar = tk->inputCopy[tk->parsingIndex];





	char 	type 	= ' ';
	char*	output	= " "; 

	type = state0(tk);

	switch (type){
		case 'm': output = "malformed"; break;
		case 'n': output = "number"; break;
		case 'w': output = "word"; break;
		default: output = "idunno"; break;

	}

	tk->type = output;

	printf("\n%s - ParsingIndex: %i - RunningSize: %i\n",output,tk->parsingIndex, tk->runningSize);
	return 0;
}

































































/* 
	This function will print the information of a token in standard output.
	FOR TESTING.
*/
void printToken(TokenizerT* ts){

	printf("\n\n-------------PRINTING\n The full input: '%s'\n", ts->inputCopy);
	printf(" The token is: '%s' of length %lu and of type: '%s' %lu\n",ts->token, strlen(ts->token), ts->type, strlen(ts->type));
	printf(" The parsing index is ( %i )\n", ts->parsingIndex);
	printf("---------------------------------\n\n");
	

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


	while(runFSM(tk) == 0){

		if(tk->runningSize != 0){			
			/* Dynamic allocation for token  */
			int size 	= tk->runningSize;
			tk->token 	= (char*)realloc(tk->token,(size+1));
			memcpy(tk->token, &tk->inputCopy[tk->parsingIndex-size],size);
			tk->token[size] = '\0';

			printToken(tk);

			tk->runningSize = 0;
		}

	}

	// /* Run token through fsm to get type */
	// //tk->type = (char*)realloc(tk->type,10);
	// tk->type = getType(tk->token);


	// tk->parsingIndex = i+1;


  	return tk->token;
}






/* 
	Agument validity checking.  Includes -help option. 
*/
void argCheck(int argc, char** argv){

	char* argNumErr = "Incorrect number of arguments given.  Use \"tokenizer -help\" for proper usage infomation.\n";  
	switch(argc){

		case 2:
			if ( strcmp(argv[1], "-help")== 0 )
			{
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





	char* test = TKGetNextToken(tokenizer);









	/*  PROGRESS NOTES TO SELF:;
			-> Substrings separated by spaces completed.
			-> Write basic type checker.  Use finite state machine design.
			-> No isspace function on linux cluster

	*/


	TKDestroy(tokenizer);
  	return 0;
}














