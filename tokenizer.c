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

	int startindex;
	int endindex;
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

	int 	tsLength 		= 	strlen(ts);
	char*	ts_ptr			= 	0;
	int 	i 				=	0;
	char* 	tokenBuffer 	= 	0;
	TokenizerT*	tokenizer 	= 	0;

	ts_ptr = (char*)malloc(sizeof(char)*(tsLength+1));
	if(ts_ptr == NULL){
		free(ts_ptr);
		return NULL;
	}
	ts_ptr = ts;

	tokenBuffer = (char*)malloc(sizeof(char)*1);
	if(tokenBuffer == NULL){
		free(ts_ptr);
		free(tokenBuffer);
		return NULL;
	}

	tokenizer->inputCopy = ts_ptr;
	tokenizer->token = tokenBuffer;
	printf("The tokenizer was initialized.\n");


	return tokenizer;


/*
	tokenizer->startindex = 0;
	tokenizer->endindex = 0;
	tokenizer->inputCopy = (char *)malloc(sizeof(char)*(tsLength+1));


	tokenizer->token = (char*)malloc(sizeof(char));
	tokenizer->type = (char*)malloc(sizeof(char));
	tokenizer->token = tokenizer->type = " ";

	printf("The tokenizer was initialized.\n");

	return tokenizer;
*/

}

/*
 * TKDestroy destroys a TokenizerT object.  It sho2uld free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
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

	char* input = tk->inputCopy;
	int i = 0;

	for(i; i<strlen(input);i++){

		if(isspace(input[i]) == 1){
			printf("\tFound the space at %i\n",i);
			break;
		}
	}
	
	int size = i - tk->startindex;
	tk->token = (char*)malloc((size+1));
	strncpy(tk->token, input, size);





  	return tk->token;
}


/* This function will print the information of a token in standard output. */
void printToken(TokenizerT* ts){

	printf("\n---PRINTING\nThe full input: '%s'\nThe token is: '%s' of size %lu\n\n",ts->inputCopy, ts->token, strlen(ts->token));

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
	printf("\nTKGetNextToken returns: '%s'\n\n",test);
	printToken(tokenizer);

	/*Why is the size so big*/

	
  return 0;
}














