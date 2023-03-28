/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*    Simple example of command processor                */
/*    Note that there are several simplifications        */
/*    E.g. Kp, Ti and Td usually are not integer values  */
/*    Code can (and should) be improved. E.g. error      */ 
/*        codes are "magic numbers" in the middle of the */
/*        code instead of being (defined) text literals  */
/* ***************************************************** */

#include <stdio.h>

#include "cmdproc.h"

/* PID parameters */
/* Note that in a real application these vars would be extern */
char Kp, Ti, Td;

/* Process variables */ 
/* Note that in a real application these vars would be extern */
int setpoint, output, error; 

/* Internal variables */
static unsigned char cmdString[MAX_CMDSTRING_SIZE]; /*ERROR deve ser UNSIGNED CHAR*/
static unsigned char cmdStringLen = 0; 

/* ************************************************************ */
/* Processes the the chars received so far looking for commands */
/* Returns:                                                     */
/*  	 0: if a valid command was found and executed           */
/* 	-1: if empty string or incomplete command found             */
/* 	-2: if an invalid command was found                         */
/* 	-3: if a CS error is detected (command not executed)        */
/* 	-4: if string format is wrong                               */
/* ************************************************************ */
int cmdProcessor(void)
{
	int i;
	int indx_SOF=0, numbs_EOF=0;
	int indx_EOF=0, numbs_SOF=0;
	unsigned char CS=0;
	
	/* Detect empty cmd string */
	if(cmdStringLen == 0)
		return -1; 
		
	/*Encontrar o indice de EOF e o SOF*/
	for(i=0; i < cmdStringLen; i++)
	 {
		if(cmdString[i] == SOF_SYM)
		{
			if(numbs_SOF==0)		/*So atribui o indice ao primeiro SOF encontrado*/		
			{
				indx_SOF=i;			
			}
			numbs_SOF++;	
		}
		
		if(cmdString[i] == EOF_SYM)
		{
			if(numbs_EOF==0)		/*So atribui o indice ao primeiro EOF encontrado*/		
			{
				indx_EOF=i;
			}
			numbs_EOF++;	
		}
	 }
	   		
     /*Validar a String Introduzida*/
     if(numbs_SOF!=1 || numbs_EOF!=1)	/*caso a mensagem tenha mais que um SOF e EOF ou nao tenha nenhum*/
	 {
		return -4;
									
     }else{ 
		    if(indx_SOF>indx_EOF)		/*caso o indece do SOF esteja depois do EOF*/	
			{
				return -4;
		    }
		  }
		  

	
	/* If a SOF was found look for commands */
	if(indx_SOF < cmdStringLen && (cmdString[indx_SOF+1] == 'P' || cmdString[indx_SOF+1] == 'S') ) 
	 {
		if(cmdString[indx_SOF+1] == 'P' && (indx_EOF-indx_SOF)== 6)
		 { /* P command detected e entre # ! tiver 5 char -> # ['P' '1' '2' '3' 'CS'] ! */	
			Kp = cmdString[indx_SOF+2];
			Ti = cmdString[indx_SOF+3];
			Td = cmdString[indx_SOF+4];
			CS = (cmdString[indx_SOF+1]+cmdString[indx_SOF+2]+cmdString[indx_SOF+3]+cmdString[indx_SOF+4]);
			
			
			if(cmdString[indx_SOF+5] == CS) /*verificar se o CS enviado e igual ao CS calculado no local*/
			{
				resetCmdString();
				return 0;				/*TUdO OK..... :)*/
			}else{
				   return -3;			/*erro na verificaço do CHECKSUM(CS)*/
				 }
		 }
		
		if(cmdString[indx_SOF+1] == 'S' && (indx_EOF-indx_SOF)== 3)
		 { /* S command detected e entre # e ! tiver 2 char -> #  ['S' 'CS'] ! */
			
			if(cmdString[indx_SOF+1] == cmdString[indx_SOF+2] ) /*verificar se o CS enviado e igual ao CS calculado no local*/
			{
				printf("Setpoint = %d, Output = %d, Error = %d", setpoint, output, error);
				resetCmdString();
				return 0;				/*TUdO OK..... :)*/
			}else{
				   return -3;			/*erro na verificaço do CHECKSUM(CS)*/
				 }
			}
				
	  }else{
		    return -2; /*comando invalido*/
		   }
	
	/* cmd string not null and SOF not found */
	return -5; 							/*valor de controlo:nenhum das condiçoes de paragem foi acinoda a cima*/

}

/* ******************************** */
/* Adds a char to the cmd string 	*/
/* Returns: 				        */
/*  	 0: if success 		        */
/* 		-1: if cmd string full 	    */
/* ******************************** */
int newCmdChar(unsigned char newChar)
{

	/* If cmd string not full add char to it */
	if (cmdStringLen < MAX_CMDSTRING_SIZE) {
		cmdString[cmdStringLen] = newChar;
			cmdStringLen +=1;
		return 0;		
	}
	
	/* If cmd string full return error */
	return -1;
}

/* ************************** */
/* Resets the commanbd string */  
/* ************************** */
void resetCmdString(void)
{
	cmdStringLen = 0;
	int i;
	for(i=0; i<=MAX_CMDSTRING_SIZE; i++)
	{
		cmdString[i]=0;		
	}
	
	return;
}
