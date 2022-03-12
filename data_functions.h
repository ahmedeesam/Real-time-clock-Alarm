/*
 * data_functions.h
 *
 * Created: 02/02/2022 10:06:01 م
 *  Author: ahmed essam
 */ 


#ifndef DATA_FUNCTIONS_H_
#define DATA_FUNCTIONS_H_
#include "uart.h"

char receive_ASCII_to_BCD();
void receive_daily(char *h);
unsigned char MSB(unsigned char x);
unsigned char LSB(unsigned char x);


#endif /* DATA_FUNCTIONS_H_ */