#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include "../usart/usart.h"

int16_t Operation(int8_t operator, uint16_t op1, uint16_t op2)
{
	int16_t res = 0;
	switch(operator)
	{
	case '+':
		res = op1 + op2;
		break;
	case '-':
		res = op1 - op2;
		break;
	case '*':
		res = op1 * op2;
		break;
	case '/':
		res = op1 / op2;
		break;
	default:
		res = -1;
		break;
	}
	return res;
}

int main()
{
	usartInit(9600);
	//timer0InteruptInit();
	int16_t broj1;
	int16_t broj2;
	int8_t str[64];
	int8_t operator;

	while(1)
	{
		usartPutString("Unesite izraz:\r\n");
		while(!usartAvailable());
		_delay_ms(100);

		broj1 = usartParseInt();
		operator = usartGetChar();
		broj2 = usartParseInt();

		usartPutString("Uneli ste izraz: ");
		sprintf(str, "%d %c %d\0", broj1, operator, broj2);
		usartPutString(str);

		sprintf(str, "= %d\0", Operation(operator, broj1, broj2));
		usartPutString(str);
		usartPutString("\r\n");
	}
	return 0;
}
