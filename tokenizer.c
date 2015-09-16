/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
	char* type;
	char* token;
	char* inputCopy;

	int parsingIndex;
};
typedef struct TokenizerT_ TokenizerT;







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

	char* 	tokenBuffer 	= 	0;
	char*	tokentype		=	0;
	TokenizerT*	tokenizer 	= 	(TokenizerT*)malloc(sizeof(TokenizerT));

	
	/* Finding heap space for the input string. 
		NOT NEEDED.  INPUT CAN BE STATIC*/
	/*
	ts_ptr = (char*)malloc(sizeof(char)*(tsLength+1));
	if(ts_ptr == NULL){
		free(ts_ptr);
		return NULL;
	}
	ts_ptr = ts; 
	*/


	/* Finding heap space for the current token. */
	tokenBuffer = (char*)malloc(sizeof(char)*1);
	if(tokenBuffer == NULL){
		free(tokenBuffer);
		return NULL;
	}

	/* Finding heap space for token type. */
	tokentype = (char*)malloc(sizeof(char)*1);
	if(tokentype == NULL){
		free(tokenBuffer);
		free(tokentype);
		return NULL;
	}




	/* Intializing tokenizer structure. */
	tokenizer->inputCopy 	= ts;
	tokenizer->token 		= tokenBuffer;
	tokenizer->type 		= tokentype;
	tokenizer->parsingIndex = 0;
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
	free(tk->type);
	free(tk->token);
	//free(tk->inputCopy);
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

	/* Token is broken off at spaces and C-keywords */

	char* 	input 	= tk->inputCopy;
	int 	i 		= tk->parsingIndex;

	if(i == strlen(input)+1){ 
		printf("No more tokens in input.\n");
		return 0;
	}

	for(i; i<strlen(input);i++){

		printf("\t%c",input[i]);
		if(input[i] == ' '){
			//printf("\tFound the space at %i\n",i);
			break;
		}

	}


	int size 	= i - tk->parsingIndex;
	tk->token 	= (char*)realloc(tk->token,(size+1));
	memcpy(tk->token, &input[tk->parsingIndex],size);
	tk->token[size] = '\0';


	tk->parsingIndex = i+1;





  	return tk->token;
}


/* This function will print the information of a token in standard output. */
void printToken(TokenizerT* ts){

	printf("\n---PRINTING\n The full input: '%s'\n", ts->inputCopy);
	printf(" The token is: '%s' of length %lu\n",ts->token, strlen(ts->token));
	printf(" The parsing index is ( %i )\n\n", ts->parsingIndex);
	

}




/* Agument validity checking.  Includes -help option. */
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
	printToken(tokenizer);



	char* test = TKGetNextToken(tokenizer);
	printToken(tokenizer);


	while(test != 0){
		test = TKGetNextToken(tokenizer);
		printToken(tokenizer);


	}


	/*  PROGRESS NOTES TO SELF:
			-> Substrings separated by spaces completed.
			-> Write basic type checker.  Use finite state machine design. 
	*/



	TKDestroy(tokenizer);	//fails for input
  	return 0;
}














