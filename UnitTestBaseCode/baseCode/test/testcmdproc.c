#include <unity.h>
#include "cmdproc.h"

void setUp(void)
{
	return;
}
void tearDown(void)
{
	return;
}

/* Constroi o cmd dentro da estrutura */
void insertStrg(const char *ptr_string)
{
	resetCmdString();
	int j;
	for(j=0;j<=MAX_CMDSTRING_SIZE; j++)
	{
		newCmdChar(*ptr_string);
		ptr_string++;	
	}
}

/* Constroi a frame adicionando o SOF, EOF e o devido CS */
void constructString(const char *ptr_string)
{
	resetCmdString();

	unsigned char CS=0;
	newCmdChar('#');				/*#*/
	if(*ptr_string=='P')
	{
		int j;
		for(j=0;j<4;j++)
		{
			newCmdChar(*ptr_string);	/*p 4 6 3*/
			CS=CS+(*ptr_string);		
			ptr_string++;	
		}
	}else{ if(*ptr_string=='S')
		   {
			newCmdChar(*ptr_string);	/*S*/
			CS=*ptr_string;
		   }
		   else
		   {
		   /*return ;*/
		   }
		
	     }
	
	
	newCmdChar(CS);					/* Check Sum*/
	
	newCmdChar('!');				/* ! */
	
}

/** Testa se a funçao apos inserido o numero maximo de elementos retorna as flags corretas
 * 	 0-> inserido com sucesso   -1->  buffer cheio  */
void test_cmdproc_adds_char(void)
{
	int i=1;
	while(i<=MAX_CMDSTRING_SIZE)
	{
		TEST_ASSERT_EQUAL_INT(Valid, newCmdChar('3'));
		i++;
	}
	TEST_ASSERT_EQUAL_INT(Err_Buf_Full, newCmdChar('3')); 
	TEST_ASSERT_EQUAL_INT(Err_Buf_Full, newCmdChar('3')); 
	
	resetCmdString();
	TEST_ASSERT_EQUAL_INT(Valid, newCmdChar('3'));       
	
}

void test_cmdProcessor_Returns_vall_Ok(void)
{
	resetCmdString(); 								
	TEST_ASSERT_EQUAL_INT(Err_Empty_str,cmdProcessor()); 				/*STRING VAZIA-> testa o reset a string e o return de cmdProcessor*/
	
    	insertStrg("234#A123S0");						/*Formato Errado->testa um cmd invalido*/
	TEST_ASSERT_EQUAL_INT(Err_str_format, cmdProcessor());

	insertStrg("234#P12300");						/*Formato Errado->testa um cmd com comando P sem EOF ->formato errado*/
	TEST_ASSERT_EQUAL_INT(Err_str_format, cmdProcessor());
	
	insertStrg("P123000000"); 						/*Formato Errado-> testa um cmd sem SOF*/
	TEST_ASSERT_EQUAL_INT(Err_str_format, cmdProcessor());
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('#');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('#'+ '1' + '2' + '3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(Err_str_format, cmdProcessor());		/*Erro no formato da frame*/
	
	resetCmdString();
	newCmdChar('!');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '2' + '3'));
	newCmdChar('#');
	TEST_ASSERT_EQUAL_INT(Err_str_format, cmdProcessor());		/*Erro no formato da frame*/
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '2' + '3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(Valid, cmdProcessor());		/*Formato CERTO-> testa um cmd correto com P*/
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar((unsigned char)('S'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(Valid, cmdProcessor());		/*FORMATO CERTO -> testa um cmd correto com S*/


    	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '2' + '5'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(Err_CS, cmdProcessor());		/*Erro no checkSum-> testa um cmd correto com P*/
	
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '6' + '3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(Err_CS, cmdProcessor());		/*Erro no CheckSum> testa um cmd correto com P*/
	
	constructString("P463");
	TEST_ASSERT_EQUAL_INT(Valid, cmdProcessor());
	
	constructString("S");
	TEST_ASSERT_EQUAL_INT(Valid, cmdProcessor());
	

}


int main(void)
{
	UNITY_BEGIN();
	
	RUN_TEST(test_cmdproc_adds_char);
	RUN_TEST(test_cmdProcessor_Returns_vall_Ok);
		
	return UNITY_END();
}
