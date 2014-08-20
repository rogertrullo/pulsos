/*
 * i2c.c
 *
 * Created: 10/08/2014 9:50:38 a. m.
 *  Author: Grupo.Sas.Uao
 */ 



#include "pulsos.h"
#include "i2c.h"

/*void I2C_WriteRegister(byte deviceRegister, byte data)
{
	I2C_Start();
	I2C_SendAddr(DS1307); // send bus address
	I2C_Write(deviceRegister); // first byte = device register address
	I2C_Write(data); // second byte = data for device register
	I2C_Stop();
}


byte I2C_ReadRegister(byte deviceRegister)
{
	byte data = 0;
	I2C_Start();
	I2C_SendAddr(DS1307); // send device bus address
	I2C_Write(deviceRegister); // set register pointer
	I2C_Start();
	I2C_SendAddr(DS1307+READ); // restart as a read operation
	data = I2C_ReadNACK(); // read the register data
	I2C_Stop(); // stop
	return data;
}*/

byte I2C_ReadNACK () // reads a data byte from slave
{
	TWCR = TW_NACK; // nack = not reading more data
	while (!TW_READY); // wait
	return TWDR;
}
byte I2C_SendAddr(byte addr)
// send bus address of slave
{
	TWDR = addr; // load device's bus address
	TWCR = TW_SEND; // and send it
	while (!TW_READY); // wait
	return (TW_STATUS);//==0x18); // return 1 if found; 0 otherwise
}

byte I2C_Write (byte data) // sends a data byte to slave
{
	TWDR = data; // load data to be sent
	TWCR = TW_SEND; // and send it
	while (!TW_READY); // wait
	return TW_STATUS;//(TW_STATUS!=0x28); // return 1 if found; 0 otherwise
}


void I2C_Init()
// at 16 MHz, the SCL frequency will be 16/(16+2(TWBR)), assuming prescalar of 0.
// so for 100KHz SCL, TWBR = ((F_CPU/F_SCL)-16)/2 = ((16/0.1)-16)/2 = 144/2 = 72.
{
	TWSR = 0; // set prescalar to zero
	TWBR = ((F_CPU/F_SCL)-16)/2; // set SCL frequency in TWI bit register
}

byte I2C_Start()
// generate a TW start condition
{
	TWCR = TW_START; // send start condition
	while (!TW_READY); // wait
	return (TW_STATUS);//==0x08); // return 1 if found; 0 otherwise
}