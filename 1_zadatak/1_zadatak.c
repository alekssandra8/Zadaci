#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../usart/usart.h"

int main()
{
	char ime[64], string[128];
	usartInit(9600);

	while(1)
	{
		usartPutString("Uneti svoje ime i prezime:\r\n");
		while(!usartAvailable());
		_delay_ms(50);

		usartGetString(ime);

		sprintf(string, "Zdravo %s :)\r\n", ime);
		usartPutString(string);
	}
	return 0;
}
