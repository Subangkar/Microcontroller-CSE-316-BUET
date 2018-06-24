/*
A simple code to display a static 'A' to the Bi-Color LED Matrix 2188.
*Here Only one color is used!!
*The rows are selected sequentially, and the column data are loaded.
*/

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <avr/interrupt.h>


#define GREEN_COLM PORTA
#define RED_COLM PORTD
#define ROW PORTB
#define OFF_FULL_COLM 0xFF
#define ON_FULL_COLM 0x00
#define ON_FULL_ROW 0xFF

#define ON_ROW 1
#define ON_COLM 0



#define UP 'u'
#define LEFT 'l'
#define DOWN 'd'
#define RIGHT 'r'
#define RED_COLOR 'r'
#define GREEN_COLOR 'g'
#define BOTH_COLOR 'b'


unsigned char displayMatrix[8]; // Row Data

void initializeDisplayMatrix()
{
	//pattern for A
	/*displayMatrix[0] = 0b11100111;
	displayMatrix[1] = 0b11011011;
	displayMatrix[2] = 0b10111101;
	displayMatrix[3] = 0b10111101;
	displayMatrix[4] = 0b10000001;
	displayMatrix[5] = 0b10111101;
	displayMatrix[6] = 0b10111101;
	displayMatrix[7] = 0b10111101;	*/

	displayMatrix[0] = 0b10000000;
	displayMatrix[1] = 0b01000000;
	displayMatrix[2] = 0b00100000;
	displayMatrix[3] = 0b00010000;
	displayMatrix[4] = 0b00001000;
	displayMatrix[5] = 0b00000100;
	displayMatrix[6] = 0b00000010;
	displayMatrix[7] = 0b00000001;

}

int ALPHA[26][8]={{0,0b01111111,0b11111111,0b11001100,0b11001100,0b11001100,0b11111111,0b01111111},

{0,0b00111100,0b01111110,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},

{0,0b11000011,0b11000011,0b11000011,0b11000011,0b11100111,0b01111110,0b00111100},

{0,0b01111110,0b10111101,0b11000011,0b11000011,0b11000011,0b11111111,0b11111111},

{0,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},

{0,0b11011000,0b11011000,0b11011000,0b11011000,0b11011000,0b11111111,0b11111111},

{0b00011111,0b11011111,0b11011000,0b11011011,0b11011011,0b11011011,0b11111111,0b11111111},

{0,0b11111111,0b11111111,0b00011000,0b00011000,0b00011000,0b11111111,0b11111111},

{0b11000011,0b11000011,0b11000011,0b11111111,0b11111111,0b11000011,0b11000011,0b11000011},

{0b11000000,0b11000000,0b11000000,0b11111111,0b11111111,0b11000011,0b11001111,0b11001111},

{0,0b11000011,0b11100111,0b01111110,0b00111100,0b00011000,0b11111111,0b11111111},

{0b00000011,0b00000011,0b00000011,0b00000011,0b00000011,0b00000011,0b11111111,0b11111111},

{0b11111111,0b11111111,0b01100000,0b01110000,0b01110000,0b01100000,0b11111111,0b11111111},

{0b11111111,0b11111111,0b00011100,0b00111000,0b01110000,0b11100000,0b11111111,0b11111111},

{0b01111110,0b11111111,0b11000011,0b11000011,0b11000011,0b11000011,0b11111111,0b01111110},

{0,0b01110000,0b11111000,0b11001100,0b11001100,0b11001100,0b11111111,0b11111111},

{0b01111110,0b11111111,0b11001111,0b11011111,0b11011011,0b11000011,0b11111111,0b01111110},

{0b01111001,0b11111011,0b11011111,0b11011110,0b11011100,0b11011000,0b11111111,0b11111111},

{0b11001110,0b11011111,0b11011011,0b11011011,0b11011011,0b11011011,0b11111011,0b01110011},

{0b11000000,0b11000000,0b11000000,0b11111111,0b11111111,0b11000000,0b11000000,0b11000000},

{0b11111110,0b11111111,0b00000011,0b00000011,0b00000011,0b00000011,0b11111111,0b11111110},

{0b11100000,0b11111100,0b00011110,0b00000011,0b00000011,0b00011110,0b11111100,0b11100000},

{0b11111110,0b11111111,0b00000011,0b11111111,0b11111111,0b00000011,0b11111111,0b11111110},

{0b01000010,0b11100111,0b01111110,0b00111100,0b00111100,0b01111110,0b11100111,0b01000010},

{0b01000000,0b11100000,0b01110000,0b00111111,0b00111111,0b01110000,0b11100000,0b01000000},

{0b11000011,0b11100011,0b11110011,0b11111011,0b11011111,0b11001111,0b11000111,0b11000011}};//characters a,b,c,d,e,f,g,...z binary codecs



int PORT[]={19,7,0,13,10,24,14,20};



// An Inplace function to rotate a N r N matrix
// by 90 degrees in anti-clockwise direction
#define N 8
int symbol[N];
int matrix[N][N];
void rotateLeftMatrix()
{
	// Consider all squares one by one
	int r,c,temp;
	for (r = 0; r < N / 2; r++)
	{
		// Consider elements in group of 4 in
		// current square
		for (c = r; c < N-r-1; c++)
		{
			// store current cell in temp variable
			temp = matrix[r][c];
			
			// move values from right to top
			matrix[r][c] = matrix[c][N-1-r];
			
			// move values from bottom to right
			matrix[c][N-1-r] = matrix[N-1-r][N-1-c];
			
			// move values from left to bottom
			matrix[N-1-r][N-1-c] = matrix[N-1-c][r];
			
			// assign temp to left
			matrix[N-1-c][r] = temp;
		}
	}
}

// splits bits of symbol into a 2d array & stores in matrix
void makeMatrix()
{
	int r,c;
	for (r = 0; r < N; r++)
	{
		for (c = 0; c < N; c++)
		{
			matrix[r][c] = (symbol[r] & (1<<(N-1-c)))!=0;
		}
	}
}

// splits bits of symbol into a 2d array & stores in matrix
void makeSymbol()
{
	int r,c;
	for (r = 0; r < N; r++)
	{
		symbol[r]=0;
		for (c = 0; c < N; c++)
		{
			symbol[r] |= (matrix[r][c] << (N-1-c));
		}
	}
}

// 1 to draw that 0 to not in symbol

void drawSymbol(int inpSymbol[],char clr,char dir){
	
	int j;
	for(j = 0; j < N; j++)
	{
		symbol[j] = inpSymbol[j];
	}
	
	makeMatrix();
	switch(dir){
		case RIGHT:
		rotateLeftMatrix();
		case DOWN:
		rotateLeftMatrix();
		case LEFT:
		rotateLeftMatrix();
		//case 'u':
	}
	makeSymbol();
	
	int i,k;
	for(k=0;k<200;k++){
		
		for(i=0;i<N;i++)
		{
			if(clr==GREEN_COLOR){
				GREEN_COLM = ~symbol[i];
				RED_COLM = OFF_FULL_COLM;
			}
			else if(clr==RED_COLOR){
				GREEN_COLM = OFF_FULL_COLM;
				RED_COLM = ~symbol[i];
			}
			else {
				GREEN_COLM = RED_COLM = ~symbol[i];
			}

			ROW = displayMatrix[i];
			_delay_us(200);
		}

	}
}




void loadLedMatrix(char clr)
{
	int l,m;

	for(m=0;m<26;m++){
		
		l=m;

		drawSymbol(ALPHA[l],GREEN_COLOR,UP);
	}

}




void DotMover(char ch)
{
	//ROW = 0xFF;
	int r,c;
	for (r=0;r<8;r++)
	{
		ROW = (1<<r);
		for (c=0;c<8;c++)
		{
			if (ch=='g')
			{
				//GREEN_COLM = ~(1<<c);
				//RED_COLM = OFF_COLM;
			}
			else if (ch=='r')
			{
				GREEN_COLM = OFF_FULL_COLM;
				RED_COLM = ~(1<<c);
			}
			else
			{
				GREEN_COLM = RED_COLM = ~(1<<c);
			}
			_delay_ms(400);
		}
		
	}
}


int main(void)
{

	DDRA  = 0xFF; // red
	DDRB  = 0xFF; // row
	DDRD  = 0xFF; // green
	

	
	initializeDisplayMatrix();
	while(1)
	{
		//loadLedMatrix(GREEN_COLOR);
		drawSymbol(ALPHA['A'-'A'],GREEN_COLOR,UP);
		_delay_ms(1000);
		drawSymbol(ALPHA['A'-'A'],GREEN_COLOR,LEFT);
		_delay_ms(1000);
		drawSymbol(ALPHA['A'-'A'],GREEN_COLOR,DOWN);
		_delay_ms(1000);
		drawSymbol(ALPHA['A'-'A'],GREEN_COLOR,RIGHT);
		_delay_ms(1000);
	}
	
	//
	//while(1){
	//DotMover('x');
	//}
}

