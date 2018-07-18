/*
 * ClockConfig.c
 *
 * Created: 18-Jul-18 1:12:37 PM
 * Author : SubangkarKr
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int main(void)
{
    DDRA=0xFF;
	while (1) 
    {
		PORTA = PORTA ^ 1;
		_delay_us(500);
    }
}

