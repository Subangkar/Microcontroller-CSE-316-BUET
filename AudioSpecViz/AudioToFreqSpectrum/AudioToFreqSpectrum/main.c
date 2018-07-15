/*
* AudioToFreqSpectrum.c
*
* Created: 15-Jul-18 8:30:23 PM
* Author : SubangkarKr
*/



//#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
//#endif

#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define forLoop(i,l) for(i=0;i<l;i++)

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
	int i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.';  // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}









#define N_SAMPLE_POINTS 7
#define OFFSET_DC_10BIT 327 // 1.6v
#define OFFSET_DC_8BIT 81 // 1.6v
#define ADC_CYCLE 125 // 1Mhz clock 8khz sampling frequency 1M/8k = 125


int analogTimeBuff[N_SAMPLE_POINTS];
int analogValue;


int adcCycDur=0;
void adcConfig()
{
	//ADMUX	= 0b01100000;
	//ADCSRA	= 0b10000001;

	ADMUX = (((0<<REFS1)|(1<<REFS0)|(1<<ADLAR))+0);
	ADCSRA =  (1<<ADEN)+3;//prescaler=3 : div=8
	
	// let max audio frequency = 4kHz
	// sampling frequency = 8kHz => time = 125us = max_time to get adc value
	// 
}

void timerConfig(){
	
	TCCR1A = 0;
	TCCR1B = 1;
	//TIMSK = (1<<OCIE1A)|(1<<OCIE1B);
	TIMSK = 0;
}


void initDataTables()
{
	int i;
	forLoop(i,N_SAMPLE_POINTS)
	{
		analogTimeBuff[i]=0;
	}
}

int readAnalogValue(int res)
{
	adcCycDur=TCNT1;
	while(ADCSRA&(1<<ADSC));
	adcCycDur=TCNT1-adcCycDur;
	analogValue = ADCL;
	if(res==10)
		analogValue = (analogValue>>6)|(ADCH<<2);
	else 
		analogValue = ADCH;
	ADCSRA |= (1<<ADSC);// start conversion
	return analogValue;
}

int main(void)
{
	DDRD = 0xFF;
	//DDRB = 0xFF;
	DDRC = 0xFF;


	float result=0x00;
	PORTB = result;

	
	adcConfig();
	timerConfig();
	//int i;
	Lcd8_Init();
	Lcd8_Clear();
	ADCSRA |= (1<<ADSC);// start conversion
	while(1)
	{
		int value = readAnalogValue(8)-OFFSET_DC_8BIT;
		result = (5*value)/1023.0;
		
		
		char lcdStringBuff[15];
		//ftoa(result,num,3);
		//strcat(num," V");
		//sprintf(lcdStringBuff,"%d V",value);
		sprintf(lcdStringBuff,"%d cycles",adcCycDur);
		Lcd8_Clear();
		Lcd8_Set_Cursor(1,1);
		Lcd8_Write_String(lcdStringBuff);

		//_delay_ms(100);
	}

}

