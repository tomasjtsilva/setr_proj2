
/** \file CMDPROC.h
 *	\author Fernando&Tomas 	
 *	\brief Este ficheiro pretende defenir as funçoes de criar uma mensagem
 *  	e leitura e valiaço dessa mensagem.
 * 	A Mensagem deve obedecer a seguinte estrutura:
 * 		-->	# CMD DATA CS ! <---
 *  - #: one byte, Start of Frame symbol
 *  - !: one byte, End of Frame symbol
 *  - CMD: one byte, command indication
 *  - DATA: variable size, command arguments
 *  - CS: one byte, checksum. Sum of numerical value of CMD and DATA[i]
 * 
 *     suportar dois comandios(CMD)
 *  - P, with 3 one-byte arguments: sets the parameters of the PID controller
 *  - S, without arguments: prints the set-point, output and erro
 *  
 * 	\date 27/03/2023
 * 	\bug Nao existem bugs detetados 
 *  
 */
#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

/* Some defines */
/* Other defines should be return codes of the functions */
/* E.g. #define CMD_EMPTY_STRING -1                      */
#define MAX_CMDSTRING_SIZE 10 /* Maximum size of the command string */ 
#define SOF_SYM '#'	          /* Start of Frame Symbol */
#define EOF_SYM '!'           /* End of Frame Symbol */

/* Function prototypes */
/** \brief Processa Valida e le a mensagem enviada. Esta Mensagem esta 
 * criada alojada internamente no modulo cmdproc.c
 * 
 * 	\author Fernando&Tomas
 * 	\param[in] void
 * 	\param[out] int: indica o estado do processamento da mensagem
 *   0: if a valid command was found and executed           
 *	-1: if empty string or incomplete command found             
 * 	-2: if an invalid command was found                         
 * 	-3: if a CS error is detected (command not executed)        
 * 	-4: if string format is wrong 
 * 
 	\date 27/03/2023
 * 
 */
int cmdProcessor(void);

/** \brief Adiciona um caracter a mensagem. 
 * 
 * 	\author Fernando&Tomas
 * 	\param[in] char: caracter a adicionar
 * 	\param[out] int: indica o estado do sucesso da inserçao
 *   0: Se o caracter foi introduzido com suceso           
 *	-1: o caracter nao foi introduzido com sucesso-> buffer cheio           
 * 
 *	\date 27/03/2023
 * 
 */
int newCmdChar(unsigned char newChar);

/** \brief reset a string, ou seja coloca o ponteiro de escrita no inicio do buffer 
 *   e escreve o valor 0 em todas a posiçoes.
 * 	\author Fernando&Tomas
 *
 *	\date 27/03/2023
 */
void resetCmdString(void);

#endif
