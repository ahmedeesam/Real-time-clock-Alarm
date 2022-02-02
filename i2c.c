/*
 * i2c.c
 *
 * Created: 02/02/2022 04:26:16 م
 *  Author: ahmed essam
 */ 

#include "i2c.h"

void I2C_INIT()
{
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = 0x04;
}

void I2C_START ()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2C_STOP()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	for(unsigned char n=0;n<=100;n++);
}

void I2C_SEND(char message)
{
	TWDR = message;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

char I2C_RECIEVE(unsigned mul)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(mul<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

void I2C_GET_SLA(int *q)
{
	int i = 0;
	
	for (int d = 0x00;d <= 0xff;d++)
	{
		I2C_START();
		I2C_SEND(d);
		i = I2C_STATUSE();
		if (i == 0x18)
		{
			*q = d;
			I2C_STOP();
			break;
		}
	}
}

char I2C_STATUSE()
{
	char l = 0;
	l = TWSR & 0xF8;
	return l;
}