/*
 * comserial.h
 *
 * Created: 09/08/2014 12:47:58 p. m.
 *  Author: Grupo.Sas.Uao
 */ 


#ifndef COMSERIAL_H_
#define COMSERIAL_H_


////////////////////ESTADO PRINCIPAL//////////////////
typedef enum
{
	espera,
	lectura_e2p,
	set_counters,
	set_fecha
	
} estado;
/////////////////////////////////////////////////



/////////////SUBESTADO SET_COUNTERS//////////////////

typedef enum
{
	inicio_sc,
	escritura_in,
	escritura_out
} estado_set_counters;

/////////////////////////////////////////////////////

/////////////SUBESTADO READ_MEM//////////////////

/*typedef enum
{
	inicio_rm,
	lee_coin_in,
	lee_coin_out,
	lee_fecha
} estado_read_mem;*/

/////////////////////////////////////////////////////



void enviar_0(char * buffer,int longitud);
void config_uart0();
void Serial_Print_String(char* string);

extern volatile estado miestado;
extern volatile  char timeout;
extern volatile uint8_t ptr_buffer;

#endif /* COMSERIAL_H_ */