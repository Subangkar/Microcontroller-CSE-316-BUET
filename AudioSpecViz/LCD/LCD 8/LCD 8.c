//
////#ifndef F_CPU
//#define F_CPU 1000000UL // 16 MHz clock speed
////#endif
//
//#define D0 eS_PORTD0
//#define D1 eS_PORTD1
//#define D2 eS_PORTD2
//#define D3 eS_PORTD3
//#define D4 eS_PORTD4
//#define D5 eS_PORTD5
//#define D6 eS_PORTD6
//#define D7 eS_PORTD7
//#define RS eS_PORTC6
//#define EN eS_PORTC7
//
//#include <avr/io.h>
//#include <util/delay.h>
//#include <string.h>
//#include <stdlib.h>
//#include <avr/interrupt.h>
//
//#include "lcd.h"
//
//
//#include <stdlib.h>
//#include <math.h>
//
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
//
//
//
//int main(void)
//{
    //DDRD = 0xFF;
	////DDRB = 0xFF;
	//DDRC = 0xFF;
//
//
	//DDRB = 0xFF;
	//ADMUX	= 0b01100000;
	//ADCSRA	= 0b10000001;
	//float result=0x00;
	//PORTB = result;
//
//
	////int i;
	//Lcd8_Init();
	//Lcd8_Clear();
	//int x = 12345;
//
//
//
	//int val;
//
	//while(1)
	//{
		//ADCSRA |= (1<<ADSC);// start conversion
		//while(ADCSRA&(1<<ADSC));
		//val = ADCL;//Ignoring <= 24.4mv
		//result = (val>>6)|(ADCH<<2);
		//result = (5*result)/1023;
		////PORTB = result;
		//
		//
		//Lcd8_Set_Cursor(1,1);
		////Lcd8_Write_String("electroSome LCD Hello World");
		//char num[10];
		//ftoa(result,num,3);
		//strcat(num," V");
		//Lcd8_Clear();		
		//Lcd8_Write_String(num);
		////for(i=0;i<15;i++)
		////{
			////_delay_ms(500);
			////Lcd8_Shift_Left();
		////}
		////for(i=0;i<15;i++)
		////{
			////_delay_ms(500);
			////Lcd8_Shift_Right();
		////}
		////Lcd8_Clear();
		////Lcd8_Write_Char('e');
		////Lcd8_Write_Char('S');
		//_delay_ms(100);
		//x+=1;
	//}
//
	//}















/*
 * main.c
 *
 *  Created on: May 27, 2018
 *      Author: masum
 */

//Receiver
#define F_CPU  1000000L
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define USART_BaudRate 9600
#define BAUD_PRESCALE  (F_CPU / (USART_BaudRate *16L) -1)
#define UART_RxCHAR() { while((UCSRA & 1<<RXC)==0); }
#define UART_TxCHAR(ch) { while(!(UCSRA & 1<<UDRE)); UDR=ch; }


void UART_Init()
{
	UCSRB |= (1<<RXEN) ;// | (1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1)  | (1<<USBS);  // 8 BIT CHARACTER
	UBRRL = (unsigned char) BAUD_PRESCALE;
	UBRRH = (unsigned char)(BAUD_PRESCALE >> 8) ;

}
/*
unsigned char UART_RxCHAR()
{
	while((UCSRA & 1<<RXC)==0);
	//PORTA = UDR;
	return UDR;
}

void UART_TxCHAR(char ch)
{
	while(!(UCSRA & 1<<UDRE));
	UDR = ch;
	_delay_ms(220);
}*/

volatile unsigned char inc;


//ISR(INT1_vect)
//{
//	//PORTA = 0x00;
//	inc++;
//	PORTA = inc;
//	_delay_ms(400);
//	GIFR |= (1<<INT1);
//}

int main(void)
{
	UART_Init();

	DDRA = 0xFF;
	PORTA = 0x8F;
	_delay_ms(500);
	PORTA = 0x0F;
	_delay_ms(3000);
	unsigned char id=0, ch, i;
	unsigned char arr[400];
	while(1)
	{
		UART_RxCHAR();
		ch = UDR;

		//PORTA = ch;
		arr[id++]=ch;
		if(id==150) break;
		//_delay_ms(500);
		//break;
	}
	PORTA=id;
	_delay_ms(4000);
	for(i=0;i<id;i++)
	{
		PORTA=arr[i];
		_delay_ms(600);
	}

	return 0;

}
