/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
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

  return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
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

  return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {

	
	
	/* Argument validity check */

	char* argNumErr = "Incorrect number of arguments given.  Use \"tokenizer -help\" for proper usage.\n";  
	switch(argc){

		case 2:
			if ( strcmp(argv[1], "-help")==0 )
			{
				fprintf(stderr, "\nProper usage:  tokenizer \" argument \"\n\n");
			}
			return -1;
	
		default: 
			fprintf(stderr, "%s\n", argNumErr);
			return -1;
	}


	char* temp = argv[1];
	printf("%s\n",temp);

	int end = 0;
	int i = 0;
	for(i=0; i<strlen(temp); i++){

		printf("%c",temp[i]);

		if(temp[i] == ' '){
			end = i;
			printf("<---  This is a separate token \n");
		}
	}
	
	

  return 0;
}














