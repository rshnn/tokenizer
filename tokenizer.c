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
	char* escapedTok;

	int parsingIndex;
	int startIndex;
	char currChar;
	int CopMode;
};
typedef struct TokenizerT_ TokenizerT;











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
		case ':': return 1;
		case '#': return 1;
		case '{': return 1;
		case '}': return 1;
		case '\\': return 1;
		case '.': return 1;
		case '+': return 1;
		case '-': return 1;
		case ';': return 1;
		case '\'': return 1;

		default: return 0;	
	}
}

int isEscape(char c, TokenizerT* tk){

	switch(c){

		case '\x00':	tk->escapedTok = "[0x00]";return 1;
		case '\x01':	tk->escapedTok = "[0x01]";return 1;
		case '\x02':	tk->escapedTok = "[0x02]";return 1;
		case '\x03':	tk->escapedTok = "[0x03]";return 1;
		case '\x04':	tk->escapedTok = "[0x04]";return 1;
		case '\x05':	tk->escapedTok = "[0x05]";return 1;
		case '\x06':	tk->escapedTok = "[0x06]";return 1;
		case '\x07':	tk->escapedTok = "[0x07]";return 1;
		case '\x08':	tk->escapedTok = "[0x08]";return 1;
		case '\x0e':	tk->escapedTok = "[0x0e]";return 1;
		case '\x0f':	tk->escapedTok = "[0x0f]";return 1;
		case '\x10':	tk->escapedTok = "[0x10]";return 1;
		case '\x11':	tk->escapedTok = "[0x11]";return 1;
		case '\x12':	tk->escapedTok = "[0x12]";return 1;
		case '\x13':	tk->escapedTok = "[0x13]";return 1;
		case '\x14':	tk->escapedTok = "[0x14]";return 1;
		case '\x15':	tk->escapedTok = "[0x15]";return 1;
		case '\x16':	tk->escapedTok = "[0x16]";return 1;
		case '\x17':	tk->escapedTok = "[0x17]";return 1;
		case '\x18':	tk->escapedTok = "[0x18]";return 1;
		case '\x19':	tk->escapedTok = "[0x19]";return 1;
		case '\x1a':	tk->escapedTok = "[0x1a]";return 1;
		case '\x1b':	tk->escapedTok = "[0x1b]";return 1;
		case '\x1c':	tk->escapedTok = "[0x1c]";return 1;
		case '\x1d':	tk->escapedTok = "[0x1d]";return 1;
		case '\x1e':	tk->escapedTok = "[0x1e]";return 1;
		case '\x1f':	tk->escapedTok = "[0x1f]";return 1;


		case '\x24':	tk->escapedTok = "[0x24]";return 1;
		case '\x40':	tk->escapedTok = "[0x40]";return 1;


		//case '\'':		tk->escapedTok = "[0x2c]";return 1 ;
		case '\"':		tk->escapedTok = "[0x22]";return 1;

		default: 	return 0;

	}

}

char nextChar(TokenizerT* tk){

	/* Reached EOF */
	if(tk->parsingIndex+1 > strlen(tk->inputCopy)-1){
		//printf("Reached eof in nextChar\n");
		tk->parsingIndex++;
		return 1;
	}


	if(isEscape(tk->inputCopy[tk->parsingIndex+1], tk)){
		//printf("Found escape char.\n");
		tk->parsingIndex++;
		return 1;

	}

	/* Next token is space */
	if( isspace(tk->inputCopy[tk->parsingIndex+1]) ){
		//printf("Found space\n");
		tk->parsingIndex++;
		return 1;
	}



	if(isOpChar(tk->inputCopy[tk->parsingIndex+1]) ){

		//printf("Found C operator char\n");

		if(!tk->CopMode){
			tk->CopMode = 1;
			tk->parsingIndex++;
			return 1;
		
		}
	}
	



	tk->parsingIndex++;
	//printf("\tCurrChar: %c, ParsingIndex: %i, StartIndex: %i\n",tk->inputCopy[tk->parsingIndex], tk->parsingIndex, tk->startIndex);
	return tk->inputCopy[tk->parsingIndex];


}











char* state30(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "not equals";
	}else{
		tk->CopMode = 0;
		return "negate";
	}
}





/* Read an escape char.  On next char. */
char* state29(TokenizerT* tk){

	tk->startIndex++;
	if(tk->currChar == '!'){
		tk->currChar = nextChar(tk);
		return state30(tk);
	}
	else
		return "escaped";


}



char* state28(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "division assignment";
	}else{
		tk->CopMode = 0;
		return "divides";
	}
}






char* state27(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "bitwise xor assignment";
	}else{
		tk->CopMode = 0;
		return "bitwise exclusive or";
	}
}




char* state26(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "modulo assignment";
	}else{
		tk->CopMode = 0;
		return "modulus";
	}
}




char* state25(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "multiplication assignment";
	}else{
		tk->CopMode = 0;
		return "indirect";
	}
}



char* state24(TokenizerT* tk){

	if(tk->currChar == '|'){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "logical or";
	}
	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "bitwise or assignment";
	}else{
		tk->CopMode = 0;
		return "vertical bar";
	}
}




char* state23(TokenizerT* tk){

	if(tk->currChar == '&'){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "logical and";
	}
	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "bitwise and assignment";
	}else{
		tk->CopMode = 0;
		return "ampersand";
	}
}






char* state22(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "equals";
	}else{
		tk->CopMode = 0;
		return "equal sign";
	}
}



char* state21(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "bitwise left shift assignment";
	}else{
		tk->CopMode = 0;
		return "shift left";
	}
}



char* state20(TokenizerT* tk){

	if(tk->currChar == '<'){
		tk->currChar = nextChar(tk);
		return state21(tk);
	}
	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "less or equal";
	}

	else{
		tk->CopMode = 0;
		return "less-than";
	}
}





char* state19(TokenizerT* tk){

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "bitwise right shift assignment";
	}else{
		tk->CopMode = 0;
		return "shift right";
	}
}




char* state18(TokenizerT* tk){

	if(tk->currChar == '>'){
		tk->currChar = nextChar(tk);
		return state19(tk);
	}
	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "greater or equal";
	}

	else{
		tk->CopMode = 0;
		return "greater-than";
	}
}






char* state17(TokenizerT* tk){


	if(tk->currChar == '+'){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "increment";
	}
	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "addition assignment";
	}

	else{
		tk->CopMode = 0;
		return "plus sign";
	}
}





char* state16(TokenizerT* tk){

	if(tk->currChar == '>'){
		tk->currChar = nextChar(tk);	
		tk->CopMode = 0;	
		return "structure pointer";
	}

	if(tk->currChar == '-'){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "decrement";
	}

	if(tk->currChar == '='){
		tk->currChar = nextChar(tk);
		tk->CopMode = 0;
		return "subtraction operation";
	}

	else{
		tk->CopMode = 0;
		return "minus sign";
	}

}



										/* C Operator stuff */
										char* state15(TokenizerT* tk){

											tk->CopMode 	= 	1;

											if(tk->currChar == '\\'){
												tk->currChar = nextChar(tk);
												return state29(tk);


											}



											if(tk->currChar == '-'){
												tk->currChar = nextChar(tk);
												return state16(tk);
											}

											if(tk->currChar == '+'){
												tk->currChar = nextChar(tk);
												return state17(tk);
											}

											if(tk->currChar == '>'){
												tk->currChar = nextChar(tk);
												return state18(tk);
											}

											if(tk->currChar == '<'){
												tk->currChar = nextChar(tk);
												return state20(tk);
											}

											if(tk->currChar == '='){
												tk->currChar = nextChar(tk);
												return state22(tk);
											}

											if(tk->currChar == '&'){
												tk->currChar = nextChar(tk);
												return state23(tk);
											}

											if(tk->currChar == '|'){
												tk->currChar = nextChar(tk);
												return state24(tk);
											}

											if(tk->currChar == '*'){
												tk->currChar = nextChar(tk);
												return state25(tk);
											}


											if(tk->currChar == '%'){
												tk->currChar = nextChar(tk);
												return state26(tk);
											}


											if(tk->currChar == '^'){
												tk->currChar = nextChar(tk);
												return state27(tk);
											}

											if(tk->currChar == '/'){
												tk->currChar = nextChar(tk);
												return state28(tk);
											}

											if(tk->currChar == '.'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "structure member";
											}


											if(tk->currChar == '~'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "1's complement";
											}

											if(tk->currChar == '?'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "question mark";
											}

											if(tk->currChar == ':'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "colon";
											}

											if(tk->currChar == ','){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "comma operator";
											}

											if(tk->currChar == '('){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "left parenthesis";
											}

											if(tk->currChar == ')'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "right parenthesis";
											}

											if(tk->currChar == '['){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "left brace";
											}

											if(tk->currChar == ']'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "right brace";
											}

											if(tk->currChar == '#'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "number sign";
											}

											if(tk->currChar == '{'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "left curly brace";
											}

											if(tk->currChar == '}'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "right curly brace";
											}
								
											if(tk->currChar == ';'){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "semicolon";
											}

											if(tk->currChar == '\''){
												tk->currChar = nextChar(tk);
												tk->CopMode = 0;
												return "apostrophe";
											}

											return "C token";

										}



char* state14(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state14(tk);
	}
	if(tk->currChar == 1)
		return "float";
	else
		return "malformed";
}



char* state13(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state14(tk);
	}
	else
		return "malformed";

}



char* state12(TokenizerT* tk){

	if(tk->currChar == '+' || tk->currChar == '-'){
		tk->currChar = nextChar(tk);
		return state13(tk);
	}
	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state14(tk);
	}

	else{

		return "malformed";
	}

}





char* state11(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state11(tk);
	}
	if(tk->currChar == 1)
		return "float";
	if(tk->currChar == 'E' || tk->currChar == 'e'){

		if(tk->inputCopy[tk->parsingIndex+1] == '-' || tk->inputCopy[tk->parsingIndex+1] == '+'){
			tk->parsingIndex++;
			tk->currChar = tk->inputCopy[tk->parsingIndex];
		}else
			tk->currChar = nextChar(tk);

		return state12(tk);
	}
	else
		return "malformed";

}





char* state10(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state11(tk);
	}
	else
		return "malformed";

}




char* state9(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		if(tk->inputCopy[tk->parsingIndex+1] == '.'){
			tk->parsingIndex++;
			tk->currChar = tk->inputCopy[tk->parsingIndex];
		}else
			tk->currChar = nextChar(tk);
			
		return state9(tk);
	}
	if(tk->currChar == '.'){
		tk->currChar = nextChar(tk);
		return state10(tk);
	}
	if(tk->currChar == 1)
		return "integer";
	if(tk->currChar == 'E' || tk->currChar == 'e'){

		if(tk->inputCopy[tk->parsingIndex+1] == '-' || tk->inputCopy[tk->parsingIndex+1] == '+'){
			tk->parsingIndex++;
			tk->currChar = tk->inputCopy[tk->parsingIndex];
		}else
			tk->currChar = nextChar(tk);

		return state12(tk);
	}
	else
		return "malformed";
}





char* state8(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state8(tk);
	}
	if(tk->currChar == 1)
		return "float";
	if(tk->currChar == 'E' || tk->currChar == 'e'){

		if(tk->inputCopy[tk->parsingIndex+1] == '-' || tk->inputCopy[tk->parsingIndex+1] == '+'){
			tk->parsingIndex++;
			tk->currChar = tk->inputCopy[tk->parsingIndex];
		}else
			tk->currChar = nextChar(tk);

		return state12(tk);
	}
	else
		return "malformed";
}



char* state7(TokenizerT* tk){

	if(isdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state8(tk);
	}
	else
		return "malformed";
}



char* state6(TokenizerT* tk){

	if(isxdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state6(tk);
	}
	if(tk->currChar == 1)
		return "hex constant";
	else
		return "malformed";
}



char* state5(TokenizerT* tk){

	if(isxdigit(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state6(tk);
	}
	else
		return "malformed";
}






char* state4(TokenizerT* tk){


	if(isOctal(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state4(tk);
	}
	if(tk->currChar == 1)
		return "octal constant";
	else
		return "malformed";
}









char* state3(TokenizerT* tk){


	if(isOctal(tk->currChar)){
		return state4(tk);
	}
	if(tk->currChar == 'x' || tk->currChar == 'X'){
		tk->currChar = nextChar(tk);
		return state5(tk);
	}
	if(tk->currChar == '.'){
		tk->currChar = nextChar(tk);
		return state7(tk);
	}
	if(tk->currChar == 1){
		return "zero";

	}else{
		return "malformed";
	}

}



char* state2(TokenizerT* tk){


	if(tk->currChar == 1)
		return "integer";

	if(isdigit(tk->currChar)){

		if(tk->currChar == '0'){
			if(tk->inputCopy[tk->parsingIndex+1] == '.'){
				tk->parsingIndex++;
				tk->currChar = tk->inputCopy[tk->parsingIndex];
			}else
				tk->currChar = nextChar(tk);

			return state3(tk);
		}
		else{
			if(tk->inputCopy[tk->parsingIndex+1] == '.'){
				tk->parsingIndex++;
				tk->currChar = tk->inputCopy[tk->parsingIndex];
			}else
				tk->currChar = nextChar(tk);
			
			return state9(tk);
		}
	}
	else
		return "malformed";

}



char* state1(TokenizerT* tk){

	if(tk->currChar == 1){
		return "word";
	}

	if(isalnum(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state1(tk);
	}

	else
		return "malformed";
}





char* state0(TokenizerT* tk){

	tk->currChar = tk->inputCopy[tk->parsingIndex];

	if(isspace(tk->currChar)){
		tk->currChar = nextChar(tk);
		tk->startIndex++;
		return state0(tk);
	}


	if(tk->parsingIndex == strlen(tk->inputCopy)){
		tk->startIndex = tk->parsingIndex;
		return "";
	}


	if(isEscape(tk->currChar, tk)){
		tk->parsingIndex++;
		return "escape character";
	}


	if(isOpChar(tk->currChar)){
		return state15(tk);
	}


	if(isalpha(tk->currChar)){
		tk->currChar = nextChar(tk);
		return state1(tk);
	}
	if(isdigit(tk->currChar)){
		return state2(tk);
	}

	else
		return "malformed";
}






/*
	runFSM will initiate the finite state machine interpreter.
	The function call will return 0 if a token is successfully created
		and will return 1 if eof is reached.
*/

int runFSM(TokenizerT* tk){


	/* If eof reached */
	if(tk->parsingIndex >= strlen(tk->inputCopy)){
		return 1;
	}


	char* 	type 	= 0;
	tk->startIndex	= tk->parsingIndex;

	type 			= state0(tk);
	tk->type 		= type;

	if(strcmp(type,"malformed")==0){
		tk->parsingIndex++;
	}

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
		printf("%s \"%s\"\n",tk->type, tk->token);

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
	tokenizer->parsingIndex = 0;
	tokenizer->startIndex	= 0;
	tokenizer->currChar		= 0;
	tokenizer->CopMode		= 0;
	tokenizer->escapedTok	= 0;

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


		if(tk->parsingIndex != tk->startIndex){				

			if(strcmp(tk->type, "escape character") == 0){
				tk->token = (char*)realloc(tk->token,(7));
				strcpy(tk->token, tk->escapedTok);
				tk->escapedTok = 0;

			}else{


			/* Dynamic allocation for token */
			size 		= tk->parsingIndex - tk->startIndex;
			tk->token 	= (char*)realloc(tk->token,(size+1));
			startAddr	= tk->startIndex;

			memcpy(tk->token, &tk->inputCopy[startAddr],size);
			tk->token[size] = '\0';}

		}else{
			/* Empty token (isspace). */
			tk->token = 0;
			tk->type = 0;
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

		//printToken1(tokenizer);
		printToken(tokenizer);

	}










	/*  PROGRESS NOTES TO SELF:;

	*/


	TKDestroy(tokenizer);
  	return 0;
}














