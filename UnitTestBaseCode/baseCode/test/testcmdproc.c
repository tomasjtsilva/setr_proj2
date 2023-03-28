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
/*
char palavra[MAX_CMDSTRING_SIZE];
*/
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

/*testa se a funçao apos inserido o numero maximo de elementos retorna as flags corretas
 * 	 0-> inserido com sucesso   -1->  buffer cheio  */
void test_cmdproc_adds_char(void)
{
	int i=1;
	while(i<=MAX_CMDSTRING_SIZE)
	{
		TEST_ASSERT_EQUAL_INT(0, newCmdChar('3'));
		i++;
	}
	TEST_ASSERT_EQUAL_INT(-1, newCmdChar('3')); 
	TEST_ASSERT_EQUAL_INT(-1, newCmdChar('3')); 
	
	resetCmdString();
	TEST_ASSERT_EQUAL_INT(0, newCmdChar('3'));       
	
}

void test_cmdProcessor_Returns_vall_Ok(void)
{
	resetCmdString(); 								
	TEST_ASSERT_EQUAL_INT(-1,cmdProcessor()); 		/*STRING VAZIA-> testa o reset a strig e o return de cmdProcessor*/
	
    insertStrg("234#A123S0");						/*Formato Errado->testa um comando invlido*/
	TEST_ASSERT_EQUAL_INT(-4, cmdProcessor());

	insertStrg("234#P12300");						/*Formato Errado->testa sms com comando P sem EOF ->formato errado*/
	TEST_ASSERT_EQUAL_INT(-4, cmdProcessor());
	
	insertStrg("P123000000"); 						/*Formato Errado-> testa sms sem SOF*/
	TEST_ASSERT_EQUAL_INT(-4, cmdProcessor());
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '2' + '3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(0, cmdProcessor());		/*Formato CERTO-> testa uma sms correta com P*/
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar((unsigned char)('S'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(0, cmdProcessor());		/*FORMATO CERTO -> testa uma sms correta com S*/


    resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '2' + '5'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(-3, cmdProcessor());		/*Erro no checkSum-> testa uma sms correta com S*/
	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar((unsigned char)('P'+ '1' + '6' + '3'));
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(-3, cmdProcessor());		/*Erro no CheckSum> testa uma sms correta com P*/

}


int main(void)
{
	UNITY_BEGIN();
	
	RUN_TEST(test_cmdproc_adds_char);
	RUN_TEST(test_cmdProcessor_Returns_vall_Ok);
		
	return UNITY_END();
}
