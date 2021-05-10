#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "../usart/usart.h"

int main()
{
	char tekst[64];
	int duzina;
	usartInit(9600);

	while(1)
	{
		usartPutString_P(PSTR("Unesite tekst:\r\n"));
		while(!usartAvailable());
		_delay_ms(50);

		usartGetString(tekst);
		usartPutString(tekst);
		usartPutString_P(PSTR("\r\n"));

		char jeste = 1;
		for(duzina = 0; tekst[duzina] != '\0'; duzina++);
		for(int i = 0; i < duzina / 2; i++)
		{
			if(tekst[i] != tekst[duzina - 1 - i])
				jeste = 0;
		}
		if(jeste)
			usartPutString_P(PSTR("Jeste palindrom!\r\n"));
		else
			usartPutString_P(PSTR("Nije palindrom!\r\n"));
	}
	return 0;
}
