/*
 * pulsos.c
 *
 * Created: 09/08/2014 12:22:25 p. m.
 *  Author: Grupo.Sas.Uao
 */ 



#include "pulsos.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "comserial.h"
#include "int_ext.h"
#include "i2c.h"






int main(void)
{
    DDRB=0xFF;
	DDRD=0x00;
	PORTD=0xFF;
	DDRE=0x00;
	PORTE=0xFF;
	
	config_uart0();
	configurar_int_ext();
	I2C_Init();
	//uint16_t dato=0;
	//guarda_eeprom((char *)&dato,2,0);
	sei();
	while(1)
    {
        //TODO:: Please write your application code 
		PORTB=PORTB^0xFF;
		/*while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=0x31;
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=TCNT1L;
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=0x33;
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=TCNT3L;*/
		_delay_ms(500);
		
		
		
		
		
		
    }
}