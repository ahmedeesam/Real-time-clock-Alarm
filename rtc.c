/*
 * rtc.c
 *
 * Created: 02/02/2022 04:26:45 م
 *  Author: ahmed essam
 */ 
#include "rtc.h"


void RTC_INIT()
{
	I2C_START();
	I2C_SEND(0xD0);
	I2C_SEND(0x07);
	I2C_SEND(0x00);
	I2C_STOP();
}

void RTC_SETtime(char s ,char m ,char h)
{
	I2C_START();
	I2C_SEND(0xD0);
	I2C_SEND(0x00);
	I2C_SEND(s);
	I2C_SEND(m);
	I2C_SEND(h);
	I2C_STOP();
}

void RTC_SETDATE(char d,char mo,char y)
{
	I2C_START();
	I2C_SEND(0xD0);
	I2C_SEND(0x04);
	I2C_SEND(d);
	I2C_SEND(mo);
	I2C_SEND(y);
	I2C_STOP();
}

void RTC_RECIEVE(char *s ,char *m ,char *h,char *d,char *mo,char *y)
{
	I2C_START();
	I2C_SEND(0xD0);
	I2C_SEND(0x00);
	I2C_STOP();
	
	I2C_START();
	I2C_SEND(0xD1);
	*s = I2C_RECIEVE(1) ;
	*m = I2C_RECIEVE(1) ;
	*h = I2C_RECIEVE(1) ;
	I2C_RECIEVE(1);
	*d = I2C_RECIEVE(1) ;
	*mo = I2C_RECIEVE(1) ;
	*y = I2C_RECIEVE(0) ;
	I2C_STOP();
}

	char hourmode (char h ,char d)
	{
		char hoursh = 0 , hoursl = 0 ,hourt = 0;
		
		hoursh = h & 0xF0;
		hoursl = h & 0x0F;
		
		if (hoursh == 0x10 && d == 0)
		{
			hourt = 0b01010000 | hoursl;
		}
		else if (hoursh == 0x10 && d == 1)
		{
			hourt = 0b01110000 | hoursl;
		}
		else if (hoursh == 0x00 && d == 0)
		{
			hourt = 0b01000000 | hoursl;
		}
		else if (hoursh == 0x00 && d == 1)
		{
			hourt = 0b01100000 | hoursl;
		}

		return hourt;
	}