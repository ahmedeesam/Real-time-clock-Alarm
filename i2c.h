/*
 * i2c.h
 *
 * Created: 02/02/2022 04:26:03 م
 *  Author: ahmed essam
 */ 

#include <avr/io.h>

#ifndef I2C_H_
#define I2C_H_

void I2C_INIT ();
void I2C_START ();
void I2C_STOP ();
void I2C_SEND (char message);
void I2C_LESTIN();
char I2C_RECIEVE();
char I2C_STATUSE();
void I2C_GET_SLA(int *q);



#endif /* I2C_H_ */