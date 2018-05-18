/*
* 4bitCounter.c
*
* Created: 13-May-18 7:17:21 PM
* Author : SubangkarKr
*/

//#define POLLING
#ifndef POLLING



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 1000000

#define _DELAY 200

#define  MAX_COUNT_MOD 15

ISR(INT2_vect)
{
	PORTA=((PORTA+1)&MAX_COUNT_MOD);
	_delay_ms(_DELAY);
	GIFR |= ((1<<INTF2));	
}

ISR(INT1_vect)
{
	PORTA=((PORTA-1)&MAX_COUNT_MOD);
	_delay_ms(_DELAY);
	GIFR |= ((1<<INTF1));
}

int main(void)
{
	DDRA|=0b00001111;
	PORTA=0x00;
	MCUCR|=0b00001100;
	MCUCSR|=0b01000000;
	GICR|=((1<<INT1)|(1<<INT2));
	sei();
	while(1);
	
}
#endif




/************************************************************************/
/* 


//#define POLLING
#ifndef POLLING



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 1000000

#define _DELAY 200

//#define  MAX_COUNT_MOD 15
volatile signed char count=0;

ISR(INT2_vect)
{
	count++;
	if(count>15)count=0;
	PORTA=count;
	_delay_ms(_DELAY);
	GIFR |= ((1<<INTF2));
	
}

ISR(INT1_vect)
{
	count--;
	if(count<0)count=15;
	PORTA=count;
	_delay_ms(_DELAY);
	GIFR |= ((1<<INTF1));
}

int main(void)
{
	DDRA|=0b00001111;
	PORTA=count;
	//PORTB = 0b11111111;
	MCUCR|=0b00001100;
	MCUCSR|=0b01000000;
	GICR|=((1<<INT1)|(1<<INT2));
	sei();
	while(1);
	
}
#endif
                                                                     */
/************************************************************************/