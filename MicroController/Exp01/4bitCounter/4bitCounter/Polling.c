/*
 * 4bitCounter.c
 *
 * Created: 13-May-18 7:17:21 PM
 * Author : SubangkarKr
 */ 

//#define POLLING

#ifdef POLLING


#include <avr/io.h>
//#define F_CPU 1000000UL
#include <util/delay.h>
#define  _DELAY_MS 400
#define  MAX_COUNT_MOD 15


#define INP_BIT_INC 0
#define INP_BIT_DEC 1


int main(void)
{	
	DDRA = 0xff;
	DDRB = 0x00;
	//DDRC = 0xff;
	PORTA = PORTB;
	//PORTD = 0b01111111;
	//PORTB = 0xff;
	
	uint8_t x=0;
    while (1) 
    {
		x=PINB;
		//PORTC=x;
		if ((x & (1<<INP_BIT_INC)))
		{
			PORTA = ((PORTA+1)&MAX_COUNT_MOD);
			_delay_ms(_DELAY_MS);
		}
		if ((x & (1<<INP_BIT_DEC)))
		{
			PORTA = ((PORTA-1)&MAX_COUNT_MOD);
			_delay_ms(_DELAY_MS);
		}
    }
}

#endif
