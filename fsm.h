#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef FSM_H_
#define FSM_H_

char 	nextChar(char* str, int currIndex);
char 	state0();
char 	state1();
char 	state2();

char* 	getType(char* in_token);



#endif /* LLNODE_H_ */
