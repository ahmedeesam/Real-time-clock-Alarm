/*
 * service_functions.c
 *
 * Created: 02/02/2022 10:10:03 م
 *  Author: ahmed essam
 */ 

#include "service_functions.h"

void record_time(char *type ,char *seconds ,char *minutes ,char *hours)
{
		/*serial_debug("Put time type:\n");
		*type = receive_ASCII_to_BCD();*/
		*type = 0x12;
		/*serial_debug("s:");
		*seconds = receive_ASCII_to_BCD();*/
		*seconds = 0x00;
		serial_debug(" h:");
		*hours   = receive_ASCII_to_BCD();
		serial_debug(" m:");
		*minutes = receive_ASCII_to_BCD();
}

void Hour_type_check(char *type,char *hours)
{
	char daiily[2];
	if (*type == 0x12)
	{
		serial_debug("press am for AM or pm for PM:");
		receive_daily(daiily);
		*hours = hourmode(*hours ,daiily);
	}
}

char hours_MSB(char *hours)
{
	char c= 0;
	c = MSB(*hours);
	if (c == '4')
	{
		serial_debug("AM");
		c = '0';
	}
	else if (c == '5')
	{
		serial_debug("AM");
		c = '1';
	}
	else if (c == '7')
	{
		serial_debug("PM");
		c = '1';
	}
	else if (c == '6')
	{
		serial_debug("PM");
		c = '0';
	}
	return c;
}

void record_date(char *day ,char *month ,char *year)
{
		serial_debug("write date:\n");
		serial_debug("d:");
		*day = receive_ASCII_to_BCD();
		serial_debug(" m:");
		*month = receive_ASCII_to_BCD();
		serial_debug(" y:");
		*year   = receive_ASCII_to_BCD();
}

void record_alarm(char *minutes ,char *hours ,char *daily)
{
	serial_debug(" h:");
	*hours   = receive_ASCII_to_BCD();
	serial_debug("\nm:");
	*minutes = receive_ASCII_to_BCD();
	serial_debug("\npm OR am\n");
	receive_daily(daily);
}

void hours_alarm(char *daily ,char *hours,char *H_alarm)
{
	char dd = 0;
		if(strcmp(daily,"am") == 0)
		{
			dd = 0;
		}
		else if(strcmp(daily,"pm") == 0)
		{
			//serial_debug("\nchecked\n");
			dd = 1;
		}
if (dd == 1)
{
	*H_alarm |= (1<<5);
}
else if (dd == 0)
{
	*H_alarm &= ~(1<<5);
}

if (((*hours & 0xF0)>>4) == 0x00)
{
	*H_alarm &= ~(1<<4);
}
else if (((*hours & 0xF0)>>4) == 0x01)
{
	*H_alarm |= (1<<4);
}
*H_alarm |= ((1<<6)|(*hours & 0x0F));
}