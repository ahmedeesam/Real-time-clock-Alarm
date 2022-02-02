/*
 * service_functions.h
 *
 * Created: 02/02/2022 10:10:14 م
 *  Author: ahmed essam
 */ 
#include "rtc.h"
#include "data_functions.h"
#include "uart.h"

#ifndef SERVICE_FUNCTIONS_H_
#define SERVICE_FUNCTIONS_H_

void record_time(char *type ,char *seconds ,char *minutes ,char *hours);
void Hour_type_check(char *type,char *hour);
void record_date(char *day ,char *month ,char *year);
char hours_MSB(char *hours);
void record_alarm(char *minutes ,char *hours ,char *daily_ala);
void hours_alarm(char *daily ,char *hours,char *H_alarm);

#endif /* SERVICE_FUNCTIONS_H_ */