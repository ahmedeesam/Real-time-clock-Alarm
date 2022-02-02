/*
 * rtc.h
 *
 * Created: 02/02/2022 04:26:34 م
 *  Author: ahmed essam
 */ 

#include "i2c.h"

#ifndef RTC_H_
#define RTC_H_


void RTC_INIT ();
void RTC_SETtime(char s ,char m ,char h);
void RTC_SETDATE(char d,char m,char y);
void RTC_RECIEVE(char *s ,char *m ,char *h,char *d,char *mo,char *y);
char hourmode (char h ,char d);


#endif /* RTC_H_ */