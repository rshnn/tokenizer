
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


static char 	currChar;
static char* 	token;
 int 		currIndex;


char nextChar(){

	if(strlen(token)-1 == currIndex){
		return 0;
	}else
		currIndex++;
		return token[currIndex];

}








char state1(){
	currChar = nextChar();
	if(currChar == 0){
		return 'w';
	}

	if(isalpha(currChar)){
		return state1();
	}else{
		return 'm';
	}

}




char state2(){
	currChar = nextChar();
	if(currChar == 0){
		return 'n';
	}
	if(isdigit(currChar)){
		return state2();
	}else
		return 'm';

}


char state0(){

	if(isalpha(currChar)){
		return state1();
	}else{
		return state2();
	}

}





char* getType(char* in_token){

	char 	type 	= ' ';
	char*	output	= " "; 
	token 		= in_token;
	currChar 	= token[0];
	currIndex 	= 0;

	type = state0();

	switch (type){
		case 'm': output = "malformed"; break;
		case 'n': output = "number"; break;
		case 'w': output = "word"; break;
		default: output = "idunno"; break;

	}

	//printf("\n%c - %s\n",type,output);

	return output;
}















