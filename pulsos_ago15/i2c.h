/*
 * i2c.h
 *
 * Created: 10/08/2014 9:49:31 a. m.
 *  Author: Grupo.Sas.Uao
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "pulsos.h"
//typedef uint8_t byte;


#define F_SCL 100000L // I2C clock speed 100 kHz
#define TW_START 0xA4 // send start condition (TWINT,TWSTA,TWEN)
#define TW_READY (TWCR & 0x80) // ready when TWINT returns to logic 1.
#define TW_STATUS (TWSR & 0xF8) // returns value of status register
#define DS1307 0xD0 // I2C bus address of DS1307 RTC
#define TW_SEND 0x84 // send data (TWINT,TWEN)#define TW_STOP 0x94 // send stop condition (TWINT,TWSTO,TWEN)
#define I2C_Stop() TWCR = TW_STOP // inline macro for stop condition#define TW_NACK 0x84 // read data with NACK (last byte)
#define READ 1

byte I2C_ReadNACK ();byte I2C_SendAddr(byte addr);byte I2C_Write (byte data);void I2C_Init();byte I2C_Start();




#endif /* I2C_H_ */