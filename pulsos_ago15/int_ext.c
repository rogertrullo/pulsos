/*
 * int_ext.c
 *
 * Created: 09/08/2014 12:56:38 p. m.
 *  Author: Grupo.Sas.Uao
 */ 
#include "int_ext.h"
#include "comserial.h"
#include "memoria.h"
#include "pulsos.h"
#include <avr/io.h>
#include <avr/interrupt.h>
# include <util/atomic.h>

char guarda_mem[]={'M','E','M','O','R','I','A'};
char ini_1[]={0x01};
char fin_1[]={0x11};
char ini_3[]={0x03};
char fin_3[]={0x13};
volatile  char en_cuenta_out=0;
volatile  uint32_t pulsos_out=0;

volatile  char en_cuenta_in=0;
volatile  uint32_t pulsos_in=0;

char buffer[10];

void configurar_int_ext(){
/*EICRA=(1<<ISC31)| (1<<ISC30)| (1<<ISC21)| (1<<ISC20);
EIMSK=(1<<INT2)| (1<<INT3);*/
TCNT1=0;
TCNT3=0;
TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS11)|(1<<CS10);//externa en T1 CTC
TCCR3B=(1<<WGM32)|(1<<CS32)|(1<<CS31)|(1<<CS30);//externa en T3 CTC
OCR1A=MULTIPLO-1;
OCR3A=MULTIPLO-1;
TIMSK|=(1<<OCIE1A);//activa interrupcion cuando hay match con OCIE1A
ETIMSK|=(1<<OCIE3A);//activa interrupcion cuando hay match con OCIE3A


}

void start_timer1()
{
	
	TCNT1=0x0000;
	TCCR1B=(1<<WGM12)|(1<<CS11)|(1<<CS10);//fcpu/64
	OCR1A=20000;//60 ms con 16mhz y presc de 64
	TIMSK|=(1<<OCIE1A);
	
}

void stop_timer1()
{
	TCCR1B=0;
}


void start_timer3()
{
	TCNT3=0x0000;
	TCCR3B=(1<<WGM32)|(1<<CS31)|(1<<CS30);//fcpu/64
	OCR3A=20000;
	ETIMSK|=(1<<OCIE3A);
}

void stop_timer3()
{
	TCCR3B=0;
}


ISR ( TIMER1_COMPA_vect )
{
	ATOMIC_BLOCK (ATOMIC_FORCEON){
	//en_cuenta_out=0;
	uint32_t dato_previo=0;
	//stop_timer1();
	
	//enviar_0(ini_1,3);
	
	enviar_0(ini_1,1);
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=0x20;
	
	
	
		
		dato_previo=lee_eeprom(DIR_IN);
		dato_previo+=MULTIPLO;
		
		char* y=(char *)&dato_previo;
		
		for(int i=0;i<NUM_BYTES_PULSOS;i++)
		{
			
			while ( !( UCSR0A & (1<<UDRE)) )
			;
			UDR0=y[i];
			
		}
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=0x20;
		
		guarda_eeprom(y,NUM_BYTES_PULSOS,DIR_IN);
		enviar_0(fin_1,1);
		//enviar_0(fin_1,4);
	
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	UDR0=0x20;
	
	
		//pulsos_out=0;
	}
	
	
}



ISR ( TIMER3_COMPA_vect )
{
	ATOMIC_BLOCK (ATOMIC_FORCEON){
	//en_cuenta_in=0;
	uint32_t dato_previo=0;
	//stop_timer3();
	
	//enviar_0(ini_3,3);
	
		enviar_0(ini_3,1);
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=0x20;
		
		
		dato_previo=lee_eeprom(DIR_OUT);
		dato_previo+=MULTIPLO;
		
		char* y=(char *)&dato_previo;
		for(int i=0;i<NUM_BYTES_PULSOS;i++)
		{
			
			while ( !( UCSR0A & (1<<UDRE)) )
			;
			UDR0=y[i];
			
		}
		
		guarda_eeprom(y,NUM_BYTES_PULSOS,DIR_OUT);
		
		//enviar_0(fin_3,4);
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=0x20;
		enviar_0(fin_3,1);
		while ( !( UCSR0A & (1<<UDRE)) )
		;
		UDR0=0x20;
	

	
	
	//pulsos_in=0;
	}
	
}