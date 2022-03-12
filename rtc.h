/*
 * rtc.h
 *
 * Created: 02/02/2022 04:26:34 م
 *  Author: ahmed essam
 */ 



#ifndef RTC_H_
#define RTC_H_

#include <string.h>
#include "i2c.h"

void RTC_INIT ();
void RTC_SETtime(char s ,char m ,char h);
void RTC_SETDATE(char d,char m,char y);
void RTC_RECIEVE(char *s ,char *m ,char *h,char *d,char *mo,char *y);
char hourmode (char h ,char *d);


#endif /* RTC_H_ */