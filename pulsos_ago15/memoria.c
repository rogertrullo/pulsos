/*
 * memoria.c
 *
 * Created: 19/01/2014 12:10:25 p.m.
 *  Author: Jhon
 */ 


//***************************************************************************
//  File Name    : i2cbus.c
//  Version      : 1.0
//  Description  : I2Cbus EEPROM AVR Microcontroller Interface
//  Author(s)    : RWB
//  Target(s)    : AVRJazz Mega168 Learning Board
//  Compiler     : AVR-GCC 4.3.0; avr-libc 1.6.2 (WinAVR 20080610)
//  IDE          : Atmel AVR Studio 4.14
//  Programmer   : AVRJazz Mega168 STK500 v2.0 Bootloader
//               : AVR Visual Studio 4.14, STK500 programmer
//  Last Updated : 28 Dec 2008
//***************************************************************************
#include <avr/io.h>
#include "pulsos.h"
#include <util/delay.h>
#include "i2c.h"
#include "memoria.h"
#include "comserial.h"

#include <avr/eeprom.h>



void I2C_WriteRegister1(uint16_t deviceRegister, byte data)
{
	byte status;
	status=I2C_Start();

	status=I2C_SendAddr(AT256); // send bus address
	
	status=I2C_Write(deviceRegister>>8); // set register pointer
	
	status=I2C_Write(deviceRegister); // set register pointer
	
	status=I2C_Write(data); // second byte = data for device register
	
	I2C_Stop();
	_delay_ms(10);
}


byte I2C_ReadRegister1(uint16_t deviceRegister)
{
	byte data = 0;
	byte status;
	status=I2C_Start();
	status=I2C_SendAddr(AT256); // send device bus address
	status=I2C_Write(deviceRegister>>8); //parte alta

	status=I2C_Write(deviceRegister); // parte baja
	
	status=I2C_Start();
	
	status=I2C_SendAddr(AT256+READ); // restart as a read operation
	
	data = I2C_ReadNACK(); // read the register data
	
	I2C_Stop(); // stop
	while(TWCR & (1<<TWSTO));
	return data;
}


void guarda_eeprom(char * buffer,int longitud,uint16_t dir){
	
	for (uint16_t i=0;i<longitud;i++)
	{
		
		I2C_WriteRegister1(dir+i,buffer[i]);
	}
	
	
}


uint32_t lee_eeprom(uint16_t dir){
	uint32_t result;
	uint8_t midata;
	char mi_buffer[NUM_BYTES_PULSOS];
	for (uint16_t i=0;i<NUM_BYTES_PULSOS;i++)
	{
		
		
		midata=I2C_ReadRegister1(dir+i);
		mi_buffer[i]=midata;
		/*while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=midata;*/
	}
	
	result=*((uint32_t*)(&mi_buffer));

	return result;
	
	
}

