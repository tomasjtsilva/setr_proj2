/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*   A few tests to the cmdProcessor                     */
/*      just to illustrate how it works                  */
/*   Shoud be improved (e.g. test more cases)            */
/*                                                       */
/* Compile with: gcc cmdproc.c main.c -o main            */
/*                                                       */
/* ***************************************************** */
#include <stdio.h>
#include "cmdproc.h"

extern char Kp, Ti, Td;

int main(void) 
{
	int res;
		
	printf("Command processor test app\n\r");
	printf("\n\n->0 ----------------------------->>>>>>>\n\r");
	resetCmdString();
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	printf("\n\n->1 ----------------------------->>>>>>>\n\r");
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	
	printf("\n\n->2 ----------------------------->>>>>>>\n\r");
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	
	printf("\n\n->3----------------------------->>>>>>>\n\r");
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '2' + '3'));
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	
	
	printf("\n\n ->4----------------------------->>>>>>>\n\r");
	resetCmdString();
	newCmdChar('#');
	newCmdChar('D');
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to D (typo, should be S): % d\n\r", res);
	
	
	
	printf("\n\n ->5----------------------------->>>>>>>\n\r");
	newCmdChar('+');
	newCmdChar('S');
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to S with wrong SOF: % d\n\r", res);
	
}
