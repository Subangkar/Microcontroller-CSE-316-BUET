/*
A simple code to display a static 'A' to the Bi-Color LED Matrix 2188.
*Here Only one color is used!!
*The rows are selected sequentially, and the column data are loaded.
*/

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/interrupt.h>

#define GREEN_COLM PORTC
#define RED_COLM PORTA
#define ROW PORTB
#define OFF_FULL_COLM 0xFF
#define ON_FULL_COLM 0x00
#define ON_FULL_ROW 0xFF

#define ON_ROW 1
#define ON_COLM 0




#define N 8
unsigned char symbol[N];
unsigned char buffer[N];


#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_init(){
	UCSRA = 0x00 ;
	UCSRB = 0x18 ;
	UCSRC = 0x86 ;
	UBRRL = 0x33 ;
	UBRRH = 0x00 ;
	
}

void makeSymbolX(){
	symbol[0]=0x00;
	symbol[1] =0x00;
	symbol[2]=0b00100100;
	symbol[3] =0b00011000;
	symbol[4] =0b00011000;
	symbol[5]=0b00100100;
	symbol[6]=0x00;
	symbol[7] = 0x00;
}

void UART_send(unsigned char data){
	while((UCSRA & (1<<UDRE))==0x00);
	UDR = data ;
}


unsigned char UART_receive(){
	//ROW = ON_FULL_ROW;
	//GREEN_COLM = ON_FULL_COLM;
	while(((UCSRA)&(1<<RXC))==0);
	//ROW = ON_FULL_ROW;
	//GREEN_COLM = OFF_FULL_COLM;
	if(UCSRA & ((1<<PE)|(1<<FE)|(1<<DOR))){
		return 0x0F;
	} 
	return UDR ;
}


//void makeSymbol();
//unsigned char ReceivedByte;
//unsigned char receiveCount=0;
//ISR(USART_RXC_vect)
//{
	////ROW=0xFF;
	////RED_COLM = OFF_FULL_COLM;
	////GREEN_COLM = OFF_FULL_COLM;
	//ReceivedByte = UDR; // Fetch the received byte value into the variable "ByteReceived"
	////UDR = ReceivedByte; // Echo back the received byte back to the computer
	//buffer[receiveCount]=ReceivedByte;
	//receiveCount++;
	//if(receiveCount>7){
		//receiveCount = 0;
		////GREEN_COLM = ON_FULL_COLM;
		//makeSymbol();
		////RED_COLM = ON_FULL_COLM;
	//}
//}


void makeSymbol(){
	for(int i=0;i<N;i++) symbol[i]=buffer[i];
}
void draw(){
	int i;
	int k;
	
	
	for(k=0;k<700;k++){
		
		for(i=0;i<N;i++)
		{
			ROW = 0;
			if(i>3){
				GREEN_COLM = ~(symbol[i]);
				RED_COLM = OFF_FULL_COLM;
			}
			else if(i<=3){
				GREEN_COLM = OFF_FULL_COLM;
				RED_COLM =  ~(symbol[i]);
			}
			

			ROW = 1<<i;
			
			_delay_us(300);
			//
		}
	}
	
	
}




void clearDot()
{
	int i;
	for (i=0;i<N;++i)
	{
		ROW = (1<<i);
		GREEN_COLM = OFF_FULL_COLM;
		RED_COLM = OFF_FULL_COLM;
	}
}





int main(void)
{
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	DDRA  = 0xFF; // red
	DDRB  = 0xFF; // row
	DDRC  = 0xFF; // green
	DDRD  = 0xFF;
	
	UART_init() ;
	unsigned char data = 0x00;
	
	//for(int i=0;i<N;i++) buffer[i]=~i;

	int count = 0;
	while(1){		
		data = UART_receive();
		buffer[count]=data;
		count++;

		if(count>7){
			count = 0;
			PORTD = 0x40;
			makeSymbol();
			//makeSymbolX();
			draw();
			//_delay_ms(100);
			PORTD = 0x00 ;
		}
		UART_send('a');	
	}
}