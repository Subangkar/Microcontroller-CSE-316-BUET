/*
* AudioToFreqSpectrum.c
*
* Created: 15-Jul-18 8:30:23 PM
* Author : SubangkarKr
*/



//#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
//#define F_CPU 8000000UL // 1 MHz clock speed
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
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

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

char lcdStringBuff[15];








#define N_SAMPLE_POINTS 7
#define OFFSET_DC_10BIT 327 // 1.6v
#define OFFSET_DC_8BIT 81 // 1.6v

#define SAMPLING_CYCLE 125 // 1Mhz clock 8khz sampling frequency 1M/8k = 125
#define SAMPLING_SLEEP_CYCLE 105


int analogTimeBuff[N_SAMPLE_POINTS];
int analogValue;
int analogBuffIndex;




ISR(TIMER1_COMPB_vect, ISR_NAKED)
{
	sei();
	sleep_cpu();
	reti();
}

int readAnalogValue(int res);
ISR (TIMER1_COMPA_vect) {
	if(analogBuffIndex<N_SAMPLE_POINTS) {
		analogTimeBuff[analogBuffIndex++]=readAnalogValue(8);//-OFFSET_DC_8BIT;
		ADCSRA |= (1<<ADSC);
		
		// must be removed
		_delay_us(100);// to show diff of voltages with time
	}
}


int adcCycDur=0;
void adcConfig()
{
	ADMUX = (((0<<REFS1)|(1<<REFS0)|(1<<ADLAR))+0);
	ADCSRA =  (1<<ADEN)+3;//prescaler=3 : div=8
	
	// let max audio frequency = 4kHz
	// sampling frequency = 8kHz => time = 125us = max_time to get adc value
	// with prescaler = 3 && sys clock = 1MHz
	// adc clock = 1M/8 = 125KHz
	// adc sample Freq = 125/13 = 9KHz => time_req = 104us < sampling, hence ok
}

void timerConfig(){
	OCR1A = SAMPLING_CYCLE;
	OCR1B = SAMPLING_SLEEP_CYCLE;
	TCCR1A = 0;
	TCCR1B = (1<<WGM12) | (1<<CS10);
	TIMSK = (1<<OCIE1A)|(1<<OCIE1B);
	//TIMSK = 0;
}


void initDataTables()
{
	analogBuffIndex=0;
	
	int i;
	forLoop(i,N_SAMPLE_POINTS)
	{
		analogTimeBuff[i]=0;
	}
}

int readAnalogValue(int res)
{
	//adcCycDur=TCNT1;
	//while(ADCSRA&(1<<ADSC));
	//adcCycDur=TCNT1-adcCycDur;
	analogValue = ADCL;
	if(res==10)
	analogValue = (analogValue>>6)|(ADCH<<2);
	else
	analogValue = ADCH;
	//ADCSRA |= (1<<ADSC);// start conversion
	return analogValue;
}


int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;


	
	adcConfig();
	timerConfig();
	Lcd8_Init();
	initDataTables();
	sei();
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
	ADCSRA |= (1<<ADSC);// start conversion
	while(1)
	{
		//int value = readAnalogValue(8)-OFFSET_DC_8BIT;
		//result = (5*value)/1023.0;
		
		
		//ftoa(result,num,3);
		//strcat(num," V");
		//sprintf(lcdStringBuff,"%d V",value);
		//sprintf(lcdStringBuff,"%d cycles",adcCycDur);
		//		Lcd8_Clear();
		//Lcd8_Set_Cursor(1,0);
		//Lcd8_Write_String(lcdStringBuff);

		//_delay_ms(100);
		if(analogBuffIndex==N_SAMPLE_POINTS){
			Lcd8_Clear();
			Lcd8_Set_Cursor(1,0);
			sprintf(lcdStringBuff,"%d %d %d %d",analogTimeBuff[0],analogTimeBuff[1],analogTimeBuff[2],analogTimeBuff[3]);
			Lcd8_Write_String(lcdStringBuff);
			Lcd8_Set_Cursor(2,0);
			sprintf(lcdStringBuff,"%d %d %d",analogTimeBuff[4],analogTimeBuff[5],analogTimeBuff[6]);
			Lcd8_Write_String(lcdStringBuff);
			analogBuffIndex=0;
			_delay_ms(100);
		}
	}

}

