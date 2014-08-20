/*
 * pulsos.h
 *
 * Created: 09/08/2014 12:45:49 p. m.
 *  Author: Grupo.Sas.Uao
 */ 


#ifndef PULSOS_H_
#define PULSOS_H_

#include <stdio.h>

#define F_CPU 16000000L
#define MULTIPLO 10
#define NUM_BYTES_PULSOS 4//tamaño en bytes del numero de pulsos que se almacena
#define NUM_BYTES_FECHA 6//tamaño en bytes de la fecha para el RTC

typedef uint8_t byte;

#define DIR_IN 0
#define DIR_OUT DIR_IN+NUM_BYTES_PULSOS
#define DIR_FECHA DIR_OUT+NUM_BYTES_PULSOS

#define USART_BAUDRATE 19200
#define BAUD_PRESCALE ((( F_CPU / ( USART_BAUDRATE * 16UL))) - 1)


/////////////////////////////////COMANDOS PRINCIPALES/////////////////////////////////////////////////////////////////////////////////
#define READ_FECHA_RTC 0x43//lee fecha del RTC
#define SET_FECHA 0x42//B para poner la fecha, seguido de 6 bytes
#define SET_COUNTERS 0x30//seguido del indicador de coin_in o out (READ_COIN_XX) y 4 bytes del numero, siendo el primer byte el LSB
#define READ_MEM 0x44//Lectura dedatos de memoria e2prom, seguido del indicador del dato a leer(COMANDOS  EEPROM).
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////COMANDOS PARA EEPROM////////////////////////////////////////////
#define READ_COIN_IN 0x31//1 coin_in
#define READ_COIN_OUT 0x32//2 coin_out
#define READ_FECHA_MEM 0xFE//fecha
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////COMANDOS PARA ELEGIR CONTADOR //////////////////////////////////////////
#define SET_COIN_IN 0x01//1 coin_in
#define SET_COIN_OUT 0x02//1 coin_out
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










#endif /* PULSOS_H_ */