/*
 * RTC_Serial.c
 *
 * Created: 02/02/2022 04:25:05 م
 * Author : ahmed essam
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util\delay.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "uart.h"
#include "rtc.h" 
#include "data_functions.h"
#include "service_functions.h"
#include "timer0.h"
#include "timer1.h"
#include "Internal_EEprom.h"
#include "var.h"

ISR (USART_RX_vect)
{
	tim1_OVinterrupt_Disable();
	
	uart_recieve_string(state);
	//serial_debug(state);
	if (strcmp(state,"start") == 0)
	{
		serial_debug("\nenter the Start Time:\n");
		record_alarm(&minutes_Sala ,&hours ,daily);
		hours_alarm(daily ,&hours ,&H_Salarm);      //for calculating the BCD value to compare with the receiver from RTC
		
		if (minutes_Sala != 0)
		{
			start_tim1_normal();
		}
	}
	else if (strcmp(state,"stop") == 0)
	{
		serial_debug("\nenter the End Time:\n");
		record_alarm(&minutes_Eala ,&hours ,daily);
		hours_alarm(daily ,&hours ,&H_Ealarm);      //for calculating the BCD value to compare with the receiver from RTC
		
		if (minutes_Eala != 0)
		{
			start_tim1_normal();
		}
	}
	else if (strcmp(state,"on") == 0)
	{
		serial_debug("\non\n");
	}
	else if (strcmp(state,"off") == 0)
	{
		serial_debug("\noff\n");
	}
	else if (strcmp(state,"time") == 0)
	{
		record_time(&type ,&seconds ,&minutes ,&hours);
		Hour_type_check(&type , &hours);
		
		RTC_SETtime(seconds,minutes,hours);		
	}
	
	tim1_OVinterrupt_Enable();
}

ISR (TIMER1_OVF_vect)
{
	RTC_RECIEVE(&seconds ,&minutes ,&hours ,&day ,&month ,&year);
	if ((minutes_Sala == minutes) && (H_Salarm == hours))
	{
		serial_debug("Start!\n");
		minutes_Sala = 0;
		H_Salarm = 0;
	}
	else if ((minutes_Eala == minutes) && (H_Ealarm == hours))
	{
		serial_debug("Stop!\n");
		minutes_Eala = 0;
		H_Ealarm = 0;
	}
	
	if ((H_Salarm == 0) && (H_Ealarm == 0))
	{
		read_tim1();
	}
}

int main(void)
{
	uart_init();
	I2C_INIT();
	RTC_INIT();
	tim1_OVinterrupt_Enable();
	uart_RX_INT_EN();
	_delay_ms(5000);
	serial_debug("Start!\n");	
	sei();
	while(1)
	{
		
	}
}
