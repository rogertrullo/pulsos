/*
 * memoria.h
 *
 * Created: 19/01/2014 11:35:12 a.m.
 *  Author: Jhon
 */ 


#ifndef MEMORIA_H_
#define MEMORIA_H_


#include "pulsos.h"

#define AT256 0xA0 // I2C bus address of  EEPROM
#define DIR_COIN_IN 0
//typedef uint8_t byte;

void guarda_eeprom(char * buffer,int longitud,uint16_t dir);
uint32_t lee_eeprom(uint16_t dir);
void I2C_WriteRegister1(uint16_t deviceRegister, byte data);byte I2C_ReadRegister1(uint16_t deviceRegister);


#endif /* MEMORIA_H_ */