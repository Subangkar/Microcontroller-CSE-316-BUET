#define MAX_VOLTAGE 5

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

#include <stdlib.h>
#include <math.h>

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


int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	
	ADMUX	= 0b01100000; // AVCC-LeftRes-ADC0
	ADCSRA	= 0b10000001; // EN-NOT_START-DIS_AUTO_TRIG-INT_FLG_0-INT_EN_0-PreScaler2
	uint16_t value = 0;
	float result=0.0;
	
	Lcd4_Init();
	
	
	while(1)
	{
		ADCSRA |= (1<<ADSC);// start conversion
		while(ADCSRA&(1<<ADSC)); // wait until finished
		value = ADCH;//(ADCH<<2)|(ADCL>>6);
		result = MAX_VOLTAGE*value/255.0;//Ignoring <= 24.4mv
		
		Lcd4_Clear();

		char num[15];
		//itoa(result,num,10);

		//sprintf(num, "%lf", result);
		ftoa(result,num,3);

		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Voltage Value: ");
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String(num);
		_delay_ms(500);
	}

}
