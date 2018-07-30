/*
 * DotDecoder.c
 *
 * Created: 25-Jul-18 2:54:04 PM
 * Author : SubangkarKr
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

#ifndef DOT_LOOP_NO
#define DOT_LOOP_NO 500
#endif



#define GREEN_COLM PORTC
#define RED_COLM PORTD
#define ROW PORTB
//#define OFF_FULL_COLM 0x00
#define OFF_FULL_COLM 0xFF
#define ON_FULL_COLM 0x00
#define ON_FULL_ROW 0xFF

#define ON_ROW 1
#define ON_COLM 0




#define N 16
unsigned char symbol[N];
unsigned char buffer[N];




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


void makeSymbol(){
	for(int i=0;i<N;i++){
		if(buffer[i]>14)	 symbol[i]=0xFF;
		else if(buffer[i]>11)symbol[i]=0x7F;
		else if(buffer[i]>9) symbol[i]=0x3F;
		else if(buffer[i]>8) symbol[i]=0x1F;
		else if(buffer[i]>7) symbol[i]=0x0F;
		else if(buffer[i]>4) symbol[i]=0x07;
		else if(buffer[i]>3) symbol[i]=0x03;
		else if(buffer[i]>1) symbol[i]=0x01;
		else				 symbol[i] = 0x00;
	}
}

void draw(){
	int i;
	int k;
	for(k=0;k<DOT_LOOP_NO;k++){
		for(i=0;i<N;i++)
		{
			//ROW = 0;
			if(i<8){
				GREEN_COLM = i;
				RED_COLM = OFF_FULL_COLM;
			}
			//else if(i==8){
				//RED_COLM = ON_FULL_COLM;
				//GREEN_COLM = OFF_FULL_COLM;
			//}
			else {
				GREEN_COLM = i;
				RED_COLM = OFF_FULL_COLM;
				//RED_COLM = ~i;
				//GREEN_COLM = OFF_FULL_COLM;
			}
			//if(i<=3){//symbol[i]<=0x0F
				//GREEN_COLM = ~i;
				//RED_COLM = OFF_FULL_COLM;
				////GREEN_COLM = ~(symbol[i]);
				////RED_COLM = OFF_FULL_COLM;
			//}
			//else {
				//RED_COLM = ~i;
				//GREEN_COLM = OFF_FULL_COLM;
				////GREEN_COLM = OFF_FULL_COLM;
				////RED_COLM =  ~(symbol[i]);
			//}
			ROW = i;
			_delay_us(300);
		}
	}
}

void clearDot()
{
	ROW = 0xFF;
	GREEN_COLM = OFF_FULL_COLM;
	RED_COLM = OFF_FULL_COLM;
}


int main(void)
{
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xFF;
	
	int row = 0;
	GREEN_COLM = OFF_FULL_COLM;
	//RED_COLM = OFF_FULL_COLM;

    while (1) 
    {
		ROW = row;
		row = (row+1)%16;
		RED_COLM = ~((1<<3)|(1<<0)); 
		//_delay_ms(2000);
		//draw();
    }
}

