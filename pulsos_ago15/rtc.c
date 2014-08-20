
#include "i2c.h"
#include "rtc.h"
#include <avr/io.h>



void I2C_WriteRegister(byte deviceRegister, byte data)
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
}


void DS1307_GetTime(byte *hours, byte *minutes, byte *seconds)
// returns hours, minutes, and seconds in BCD format
{
	*hours = I2C_ReadRegister(HOURS_REGISTER);
	*minutes = I2C_ReadRegister(MINUTES_REGISTER);
	*seconds = I2C_ReadRegister(SECONDS_REGISTER);
	if (*hours & 0x40) // 12hr mode:
	*hours &= 0x1F; // use bottom 5 bits (pm bit = temp & 0x20)
	else *hours &= 0x3F; // 24hr mode: use bottom 6 bits
}

void DS1307_GetDate(byte *months, byte *days, byte *years)
// returns months, days, and years in BCD format
{
	*months = I2C_ReadRegister(MONTHS_REGISTER);
	*days = I2C_ReadRegister(DAYS_REGISTER);
	*years = I2C_ReadRegister(YEARS_REGISTER);
}void SetTimeDate(byte year,byte month,byte day,byte hour,byte minute,byte second)
// simple, hard-coded way to set the date 8/13/2013 at 8:51 PM
{
	I2C_WriteRegister(MONTHS_REGISTER, month);
	I2C_WriteRegister(DAYS_REGISTER, day);
	I2C_WriteRegister(YEARS_REGISTER, year);
	I2C_WriteRegister(HOURS_REGISTER, hour);
	I2C_WriteRegister(MINUTES_REGISTER, minute);
	I2C_WriteRegister(SECONDS_REGISTER, second);
}