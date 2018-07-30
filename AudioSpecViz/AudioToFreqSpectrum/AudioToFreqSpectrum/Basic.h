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


//#define LCD_BUFFER_SIZE 30
//char lcdStringBuff[LCD_BUFFER_SIZE];

//void LCDPrintInt(int32_t x,int row)
//{
////	Lcd4_Clear();
				//
	//Lcd4_Set_Cursor(row,0);
	//sprintf(lcdStringBuff,"%ld",x);
	//Lcd4_Write_String(lcdStringBuff);
//}

#endif /* BASIC_H_ */