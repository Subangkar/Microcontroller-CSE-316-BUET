/*
 * ClockConfig.c
 *
 * Created: 18-Jul-18 1:12:37 PM
 * Author : SubangkarKr
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

#define FREQ_TO_GEN 1500
#define usDELAY (1000000/FREQ_TO_GEN)

int main(void)
{
    DDRA=0xFF;
	while (1) 
    {
		PORTA = PORTA ^ 1;
		_delay_us(usDELAY);
    }
}

