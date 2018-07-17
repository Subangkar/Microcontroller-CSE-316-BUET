/*
 * Basic.h
 *
 * Created: 16-Jul-18 3:41:10 AM
 *  Author: SubangkarKr
 */ 


#ifndef BASIC_H_
#define BASIC_H_



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

//// reverses a string 'str' of length 'len'
//void reverse(char *str, int len)
//{
	//int i=0, j=len-1, temp;
	//while (i<j)
	//{
		//temp = str[i];
		//str[i] = str[j];
		//str[j] = temp;
		//i++; j--;
	//}
//}
//
//// Converts a given integer x to string str[].  d is the number
//// of digits required in output. If d is more than the number
//// of digits in x, then 0s are added at the beginning.
//int intToStr(int x, char str[], int d)
//{
	//int i = 0;
	//while (x)
	//{
		//str[i++] = (x%10) + '0';
		//x = x/10;
	//}
	//
	//// If number of digits required is more, then
	//// add 0s at the beginning
	//while (i < d)
	//str[i++] = '0';
	//
	//reverse(str, i);
	//str[i] = '\0';
	//return i;
//}
//
//// Converts a floating point number to string.
//void ftoa(float n, char *res, int afterpoint)
//{
	//// Extract integer part
	//int ipart = (int)n;
	//
	//// Extract floating part
	//float fpart = n - (float)ipart;
	//
	//// convert integer part to string
	//int i = intToStr(ipart, res, 0);
	//
	//// check for display option after point
	//if (afterpoint != 0)
	//{
		//res[i] = '.';  // add dot
		//
		//// Get the value of fraction part upto given no.
		//// of points after dot. The third parameter is needed
		//// to handle cases like 233.007
		//fpart = fpart * pow(10, afterpoint);
		//
		//intToStr((int)fpart, res + i + 1, afterpoint);
	//}
//}

#endif /* BASIC_H_ */