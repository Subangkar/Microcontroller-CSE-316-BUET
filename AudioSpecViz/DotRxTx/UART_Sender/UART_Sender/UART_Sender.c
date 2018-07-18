

#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

unsigned char symbol[8];
unsigned char finalSymbol[8];

void makeSymbol(){
	symbol[0]=0x00;
	symbol[1] =0x00;
	symbol[2]=0b00100100;
	symbol[3] =0b00011000;
	symbol[4] =0b00011000;
	symbol[5]=0b00100100;
	symbol[6]=0x00;
	symbol[7] = 0x00;
}
void UART_init(){
	UCSRA = 0x00 ;
	UCSRB = 0x18 ;
	UCSRC = 0x86 ;
	UBRRL = 0x33 ;
	UBRRH = 0x00 ;
	
}

void UART_send(unsigned char data){
	while((UCSRA & (1<<UDRE))==0);
	UDR = data ;
}
unsigned char UART_receive(){
	while(((UCSRA)&(1<<RXC))==0);
	return UDR ;
}

int main(void)
{
	DDRB = 0xFF ;
	DDRA = 0xFF ;
	DDRD = 0xFF ;
	makeSymbol();
	UART_init() ;
	int i = 0;
	unsigned char data=0xFF;
	while(1){
		data = symbol[i];
		
		UART_send(data);
		PORTA = 0xFF;
		_delay_ms(100) ;
		PORTA = 0x00 ;
		_delay_ms(100) ;
		data = UART_receive();
		
		PORTB = 0xFF ;
		_delay_ms(100) ;
		PORTB = 0x00 ;
		_delay_ms(100) ;
		
		i = (i+1)%8;
			//draw();			
	}
}


