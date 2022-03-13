/*
 * data_functions.c
 *
 * Created: 02/02/2022 10:06:19 م
 *  Author: ahmed essam
 */ 
#include "data_functions.h"

unsigned char MSB(unsigned char x)           //Display Most Significant Bit of BCD number
{
	return ((x >> 4) + '0');
}

unsigned char  LSB(unsigned char x)          //Display Least Significant Bit of BCD number
{
	return ((x & 0x0F) + '0');
}

char receive_ASCII_to_BCD()
{
	char received1 = 0;
	char received2 = 0;

	received1 = uart_recieve_ch();
	uart_send_ch(received1);
	
	received2 = uart_recieve_ch();
	uart_send_ch(received2);
	
	received1 = ((received1 & 0x0F)<<4);
	received1 |= (received2 & 0x0F);
	
	return received1;
}

void receive_daily(char *h)
{
	for (unsigned char i = 0;i <= 1;i++)
	{
		h[i] = uart_recieve_ch();
	}
	h[2] = '\0';
	//serial_debug(h);
	//serial_debug("\n");
}

/*void BCD_to_ascii_display(char a)
{
	char b ,c;
	b = ((a & 0x0F) + '0');
	c = (((a & 0xF0)>>4) + '0');
	uart_send_ch(c);
	uart_send_ch(b);
}*/
