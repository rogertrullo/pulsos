
#ifndef RTC_H
#define RTC_H

#include "pulsos.h"

//#include "sas.h"

/*#define F_SCL 100000L // I2C clock speed 100 kHz
#define TW_START 0xA4 // send start condition (TWINT,TWSTA,TWEN)
#define TW_READY (TWCR & 0x80) // ready when TWINT returns to logic 1.
#define TW_STATUS (TWSR & 0xF8) // returns value of status register
#define DS1307 0xD0 // I2C bus address of DS1307 RTC
#define TW_SEND 0x84 // send data (TWINT,TWEN)
#define I2C_Stop() TWCR = TW_STOP // inline macro for stop condition
#define READ 1
#define MINUTES_REGISTER 0x01
#define HOURS_REGISTER 0x02
#define DAYOFWK_REGISTER 0x03
#define DAYS_REGISTER 0x04
#define MONTHS_REGISTER 0x05
#define YEARS_REGISTER 0x06