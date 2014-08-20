/*
 * comserial.c
 *
 * Created: 09/08/2014 12:47:12 p. m.
 *  Author: Grupo.Sas.Uao
 */ 
#include "pulsos.h"
#include "memoria.h"
#include "rtc.h"
#include "comserial.h"
#include <avr/io.h>
#include <avr/interrupt.h>


volatile estado miestado=espera;
volatile estado_set_counters miestado_sc=inicio_sc;
//volatile estado_read_mem mi_read_mem=inicio_rm;
volatile char timeout=0;

volatile uint8_t ptr_buffer=0;
volatile char buffer_trama[10];


void config_uart0(){//xbee
	
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	UCSR0B|=(1<<RXCIE0);//activamos el rx, el tx y la interrupcion de recepcion
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//8 bits
	UBRR0H=(unsigned char)BAUD_PRESCALE>>8;
	UBRR0L=(unsigned char)BAUD_PRESCALE;
	
	
}


void enviar_0(char * buffer,int longitud)
{
	
	for(int i=0;i<longitud;i++)
	{
		
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=buffer[i];
		
	}
	/*PORTB=PORTB^0xFF;
	uint32_t x=255;
	char* y=(char *)&x;
	for(int i=0;i<4;i++)
	{
		
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=y[i];
		
	}*/
	


}

////////////////////////////Interrupcion serial//////////////
ISR(USART0_RX_vect)
{
	char dato_recibido=UDR0;
	uint32_t dato=0;
	char* y=0;
	byte hours, minutes, seconds,months, days, years;
	
	switch(miestado){
		
		case espera:
		if(dato_recibido==SET_COUNTERS){
			
			miestado=set_counters;
		}
		else if(dato_recibido==READ_FECHA_RTC){
			DS1307_GetDate(&months,&days,&years);
			enviar_fecha(months, days, years);
			
			
			DS1307_GetTime(&hours,&minutes,&seconds);
			enviar_hora(hours, minutes, seconds);
			miestado=espera;
		}
		else if(dato_recibido==SET_FECHA){
			miestado=set_fecha;
			
		}
		else if(dato_recibido==READ_MEM){
			miestado=lectura_e2p;
			
		}
		
		
		
		
		break;
		
		case set_counters:
		
		if(miestado_sc==inicio_sc){
			if(dato_recibido==SET_COIN_IN){
				miestado_sc=escritura_in;			
			}
			else if(dato_recibido==SET_COIN_OUT){
				miestado_sc=escritura_out;			
				
			}		
			
		}
		else if(miestado_sc==escritura_in){
			if(ptr_buffer<NUM_BYTES_PULSOS-1){
				buffer_trama[ptr_buffer]=dato_recibido;
				ptr_buffer++;				
				
			}
			else{
				buffer_trama[ptr_buffer]=dato_recibido;
				ptr_buffer=0;
				miestado_sc=inicio_sc;
				miestado=espera;
				guarda_eeprom(buffer_trama,NUM_BYTES_PULSOS,DIR_IN);
							
				
			}
			
		}
		else if(miestado_sc==escritura_out){
			
			if(ptr_buffer<NUM_BYTES_PULSOS-1){
				buffer_trama[ptr_buffer]=dato_recibido;
				ptr_buffer++;
				
			}
			else{
				buffer_trama[ptr_buffer]=dato_recibido;
				ptr_buffer=0;
				miestado_sc=inicio_sc;
				miestado=espera;
				guarda_eeprom(buffer_trama,NUM_BYTES_PULSOS,DIR_OUT);				
				
			}			
			
		}
			
		break;
		
		case set_fecha:
		if(ptr_buffer<NUM_BYTES_FECHA-1){
			buffer_trama[ptr_buffer]=dato_recibido;
			ptr_buffer++;
			
		}
		else{
			buffer_trama[ptr_buffer]=dato_recibido;
			ptr_buffer=0;
			miestado=espera;
			SetTimeDate(buffer_trama[0],buffer_trama[1],buffer_trama[2],buffer_trama[3],buffer_trama[4],buffer_trama[5]);//año-mes-dia-hora-minuto-segundo
			byte hours, minutes, seconds,months, days, years;
			
			DS1307_GetDate(&months,&days,&years);
			enviar_fecha(months, days, years);
			
			DS1307_GetTime(&hours,&minutes,&seconds);
			enviar_hora(hours, minutes, seconds);
			
		}
		
		break;
		
		case lectura_e2p:

		if(dato_recibido==READ_COIN_IN){
			
			miestado=espera;
			dato=lee_eeprom(DIR_IN);
			y=(char *)&dato;
			for(int i=0;i<NUM_BYTES_PULSOS;i++)
			{
				
				while ( !( UCSR0A & (1<<UDRE)) )
				;
				UDR0=y[i];
				
			}
			
			
		}
		else if(dato_recibido==READ_COIN_OUT){
			
			miestado=espera;
			dato=lee_eeprom(DIR_OUT);
			y=(char *)&dato;
			for(int i=0;i<NUM_BYTES_PULSOS;i++)
			{
				
				while ( !( UCSR0A & (1<<UDRE)) )
				;
				UDR0=y[i];
				
			}
			
		}
		else if(dato_recibido==READ_FECHA_MEM){
			
			miestado=espera;
			dato=lee_eeprom(DIR_FECHA);
			y=(char *)&dato;
			for(int i=0;i<NUM_BYTES_PULSOS;i++)
			{
				
				while ( !( UCSR0A & (1<<UDRE)) )
				;
				UDR0=y[i];
				
			}
			
		}
		
		break;
		
				
	}
	
	
	
	
		
	/*char reset=0xFF;
	uint32_t dato=0;
	volatile char* y=0;
	if(dat_recibio=='0'){//0 resetea memoria a ceros
		guarda_eeprom((char *)&dato,NUM_BYTES_PULSOS,DIR_IN);
		guarda_eeprom((char *)&dato,NUM_BYTES_PULSOS,DIR_OUT);
		
		TCNT1=0;
		TCNT3=0;
		enviar_0(&reset,1);
		
	}
	else if(dat_recibio=='1'){//manda coin_in
		dato=lee_eeprom(DIR_IN);
		
		y=(char *)&dato;
		for(int i=0;i<NUM_BYTES_PULSOS;i++)
		{
			
			while ( !( UCSR0A & (1<<UDRE)) )
			;
			UDR0=y[i];
			
		}
		
		
	}
	else if(dat_recibio=='2'){//manda coin_out
		dato=lee_eeprom(DIR_OUT);
		y=(char *)&dato;
		for(int i=0;i<NUM_BYTES_PULSOS;i++)
		{
			
			while ( !( UCSR0A & (1<<UDRE)) )
			;
			UDR0=y[i];
			
		}
		
		
	}*/
	
	
	
	
	
	//enviar_0(&dato_prueba,1);
	
}


void enviar_fecha(byte months,byte days,byte years){
	
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=days;
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=months;
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=years;
	
	
}


void enviar_hora(byte horas,byte minutos,byte segundos){
	
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=horas;
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=minutos;
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=segundos;
	
	
}
