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
<<<<<<< HEAD
	printf("\n\n->0 ----------------------------->>>>>>>\n\r");
	resetCmdString();
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	printf("\n\n->1 ----------------------------->>>>>>>\n\r");
=======
	resetCmdString();
	res=cmdProcessor();
>>>>>>> 1c902996f3a4d4cfc0a57923b9f36830f73127a2
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
<<<<<<< HEAD
	
	printf("\n\n->2 ----------------------------->>>>>>>\n\r");
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
	
	printf("\n\n->3----------------------------->>>>>>>\n\r");
=======
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
>>>>>>> 1c902996f3a4d4cfc0a57923b9f36830f73127a2
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
<<<<<<< HEAD
	newCmdChar((unsigned char)('P'+ '1' + '2' + '3'));
=======
	newCmdChar((unsigned char)('P'+'1'+'2'+'3'));
>>>>>>> 1c902996f3a4d4cfc0a57923b9f36830f73127a2
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to P 1 2 3: %d, Kp=%c,Ti=%c,Td=%c \n\r", res, Kp, Ti, Td);
	
<<<<<<< HEAD
	
	
	printf("\n\n ->4----------------------------->>>>>>>\n\r");
	resetCmdString();
=======
>>>>>>> 1c902996f3a4d4cfc0a57923b9f36830f73127a2
	newCmdChar('#');
	newCmdChar('D');
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to D (typo, should be S): % d\n\r", res);
	
<<<<<<< HEAD
	
	
	printf("\n\n ->5----------------------------->>>>>>>\n\r");
=======
>>>>>>> 1c902996f3a4d4cfc0a57923b9f36830f73127a2
	newCmdChar('+');
	newCmdChar('S');
	newCmdChar('!');
	res=cmdProcessor();
	printf("cmdProcessor output to S with wrong SOF: % d\n\r", res);
	
}
