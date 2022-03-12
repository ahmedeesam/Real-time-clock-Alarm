/*
 * RTC_Serial.c
 *
 * Created: 02/02/2022 04:25:05 م
 * Author : ahmed essam
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util\delay.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "uart.h"
#include "rtc.h" 
#include "data_functions.h"
#include "service_functions.h"

char seconds ,minutes ,hours ,day ,month ,year ,type ,sget , check_S, check_E ,minutes_Sala ,H_Salarm, minutes_Eala ,H_Ealarm;
char time[] = "00:00:00";
char state[6], daily[2];
char date[] = "2000/00/00";

int main(void)
{
	uart_init();
	uart_RX_INT_EN();
	I2C_INIT();
	RTC_INIT();
	_delay_ms(5000);
	serial_debug("Start!\n");	
		while(1)
		{
			serial_debug("\npress A to set alarm or D to display time or M to modify:\n");
			sget = uart_recieve_ch();
			if (sget == 'D')
			{
				RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
				
				serial_debug("Time:\n");
				time[0] = hours_MSB(&hours);	
				time[1] = LSB(hours);
				time[3] = MSB(minutes);
				time[4] = LSB(minutes);
				time[6] = MSB(seconds);
				time[7] = LSB(seconds);
				date[2] = MSB(year);
				date[3] = LSB(year);
				date[5] = MSB(month);
				date[6] = LSB(month);
				date[8] = MSB(day);
				date[9] = LSB(day);

				
				serial_debug(time);
				serial_debug("\nDate:");
				serial_debug(date);
				serial_debug("\n");
			} 
			else if (sget == 'M')
			{
				record_time(&type ,&seconds ,&minutes ,&hours);
				Hour_type_check(&type , &hours);
				
				record_date(&day ,&month ,&year);

				RTC_SETtime(seconds,minutes,hours);
				RTC_SETDATE(day,month,year);
			}
			else if (sget == 'A')
			{
			uart_recieve_string(state);
			//serial_debug(state); 
			if (strcmp(state,"time") == 0) 
			{
serial_debug("\nenter the Start Time:\n");
record_alarm(&minutes_Sala ,&hours ,daily);
hours_alarm(daily ,&hours ,&H_Salarm);      //for calculating the BCD value to compare with the receiver from RTC
serial_debug("\nenter the End Time:\n");
record_alarm(&minutes_Eala ,&hours ,daily);
hours_alarm(daily ,&hours ,&H_Ealarm);      //for calculating the BCD value to compare with the receiver from RTC
check_S = 0;
check_E = 0;
serial_debug("Waiting to Start:\n");

while(check_S == 0)
{
	RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
	if ((minutes_Sala == minutes) && (H_Salarm == hours))
	{
		serial_debug("Start!\n");
		check_S = 1;
	}
	_delay_ms(5000);
}
serial_debug("Waiting to Stop:\n");
while(check_E == 0)
{
	RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
	if ((minutes_Eala == minutes) && (H_Ealarm == hours))
	{
		serial_debug("Stop!\n");
		check_E = 1;
	}
	_delay_ms(5000);
}			
			}
			else if (strcmp(state,"control") == 0)
			{
				
			}
		}
	}
}

/*serial_debug("\nenter the Start Time:\n");
				record_alarm(&minutes_Sala ,&hours ,daily_S);
				hours_alarm(daily_S ,&hours ,&H_Salarm);      //for calculating the BCD value to compare with the receiver from RTC
				serial_debug("\nenter the End Time:\n");
				record_alarm(&minutes_Eala ,&hours ,daily_E);
				hours_alarm(daily_E ,&hours ,&H_Ealarm);      //for calculating the BCD value to compare with the receiver from RTC
				check = 0;
				check_S = 0;
				check_E = 0;
				serial_debug("Waiting to Start:\n");

				while(check_S == 0)
				{
					RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
					if ((minutes_Sala == minutes) && (H_Salarm == hours))
					{
						serial_debug("Start!\n");
						check_S = 1;
					}
					_delay_ms(5000);
				} 
				serial_debug("Waiting to Stop:\n");
				while(check_E == 0)
				{
					RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
					if ((minutes_Eala == minutes) && (H_Ealarm == hours))
					{
						serial_debug("Stop!\n");
						check_E = 1;
						check = 0;
					}
					_delay_ms(5000);
				}*/

/*			{
serial_debug("enter the alarm:\n");
record_alarm(&minutes_ala ,&hours ,daily);
hours_alarm(daily ,&hours ,&H_alarm);      //for calculating the BCD value to compare with the receiver from RTC
check = 0;
while(check == 0)
{
RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
if ((minutes_ala == minutes) && (H_alarm == hours))
{
serial_debug("Start!\n");
check = 1;
}
_delay_ms(5000);
}
}*/