#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "../usart/usart.h"

void ConvertToHex(int8_t *s, uint16_t num)
{
	uint16_t temp = num;
	uint8_t index = 0;

	while(temp > 0)
	{
		if(temp % 16 < 10)
			s[index] = temp % 16 + '0';
		else
			s[index] = temp % 16 - 10 + 'A';

		temp = temp / 16;
		index++;
	}

	for(uint8_t i = 0; i < index/2; i++)
	{
		s[i] ^= s[index - 1 - i];
		s[index - 1 - i] ^= s[i];
		s[i] ^= s[index - 1 - i];
	}

	s[index] = '\0';
}

int main()
{
	usartInit(9600);
	//timer0InteruptInit();
	int16_t broj;
	int8_t str[64];

	while(1)
	{
		usartPutString("Unesite decimalan broj:\r\n");
		while(!usartAvailable());
		_delay_ms(100);

		broj = usartParseInt();

		usartPutString("Uneti broj u hexadec. zapisu:\r\n");
		ConvertToHex(str, broj);
		usartPutString(str);
		usartPutString("\r\n");
	}
	return 0;
}
