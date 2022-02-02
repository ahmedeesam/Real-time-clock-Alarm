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

char seconds ,minutes ,hours ,day ,month ,year ,type ,sget ,check ,minutes_ala ,daily ,H_alarm;
char time[] = "00:00:00";
char date[] = "2000/00/00";

int main(void)
{
	uart_init();
	I2C_INIT();
	RTC_INIT();
	_delay_ms(3000);
		
		while(1)
		{
			serial_debug("press A to set alarm or D to display time or M to modify:\n");
			sget = uart_recieve_ch();
			if (sget == 'D')
			{
				RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
				
				serial_debug("Time:");
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
				serial_debug("enter the alarm:\n");
				record_alarm(&minutes_ala ,&hours ,&daily);
				hours_alarm(&daily ,&hours ,&H_alarm);      //for calculating the BCD value to compare with the receiver from RTC
				check = 0;
				while(check == 0)
				{
					RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
					if ((minutes_ala == minutes) && (H_alarm == hours))
					{
						serial_debug("ALARM!\n");
						check = 1;
					}
					_delay_ms(5000);
				}
			}
		}
}

