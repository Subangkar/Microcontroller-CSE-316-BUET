/************************************************************************
	graph.c

    FFT Audio Analysis
    Copyright (C) 2011 Simon Inns

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com

************************************************************************/

#ifndef GRAPH_C
#define GRAPH_C

// Global includes
#include <htc.h>

// Local includes
#include "hardware.h"
#include "graph.h"

// Write a byte directly to the screen hardware (quick version)
void fLcdWrite(unsigned char cmdType, unsigned char bank, unsigned char byte)
{
	// Wait for the busy flag to clear
	GLCD_DATADIRECTION = GLCD_READ;
	GLCD_RW = READ;
	GLCD_RS = GLCD_CMD;
	
	do
	{
		// Strobe the EN line
		GLCD_EN = 1;
		__delay_us(ENSTROBEDELAY);
		GLCD_EN = 0;
	} while (GLCD_DB7 == 1);

	// Select the command type
	GLCD_RS = cmdType;

	// Select the screen bank
	if (bank == 0)
	{
		GLCD_CS1 = 1;
		GLCD_CS2 = 0;
	}
	else
	{
		GLCD_CS1 = 0;
		GLCD_CS2 = 1;
	}

	// Place the byte on the databus
	GLCD_DATADIRECTION = GLCD_WRITE;
	GLCD_RW = WRITE;
	GLCD_DATABUS = byte;

	// Strobe the EN line
	GLCD_EN = 1;
	__delay_us(ENSTROBEDELAY);
	GLCD_EN = 0;
}

// Global to hold the display data (required for output damping)
short displayData[32];

// Plot the output graph
void drawFftGraph(short inputData[])
{
	short inputValue;
	
	// Scale the input data to 0-63 and perform the dampening of the display
	for (unsigned char counter = 1; counter < 32; counter++)
	{
		// Scale the input data for the display (linear) x1 or x8
		if (SWITCH0 == 0) inputValue = inputData[counter] * 8;
		else inputValue = inputData[counter];
		if (inputValue > 181) inputValue = 181;
		
		// Apply a linear or logarithmic conversion on the data
		if (SWITCH1 == 0) inputValue = (short)logTable[inputValue];
		else inputValue = (short)linTable[inputValue];
		
		// Perform damping on the displayed output
		if (inputValue > displayData[counter]) displayData[counter] = inputValue;
		else displayData[counter] -= 10;
		if (displayData[counter] < 0) displayData[counter] = 0;
	}
	
	// Our FFT animation speed is dependent on how fast the LCD can
	// be updated, so here we use a bargraph drawing routine which
	// is highly optimised to the manner in which the LCD is updated.
	unsigned char xByte, requiredY, y, pointer;
	for (y = 0; y < 8; y++)
	{
		// Move to the correct screen page
		
		// Left bank
		fLcdWrite(GLCD_CMD, 0, y | 0b10111000);
		fLcdWrite(GLCD_CMD, 0, 0b01000000);
		
		// Right bank
		fLcdWrite(GLCD_CMD, 1, y | 0b10111000);
		fLcdWrite(GLCD_CMD, 1, 0b01000000);
		
		unsigned char xPos = 0;
		
		// We only draw buckets 1 to 31 (bucket 0 is invalid)
		for (pointer = 0; pointer < 32; pointer++)
		{
			xByte = 0;
			requiredY = 63 - displayData[pointer];
			
			// Either fill the whole byte or
			// left shift according to the remainder of 
			// the division to get the right number of pixels
			if (requiredY <= y * 8) xByte = 0b11111111;
			else if (requiredY / 8 <= y) xByte = 0b11111111 << (requiredY % 8);	
			
			if (xPos < 64) fLcdWrite(GLCD_DATA, 0, xByte); // 1/3 of bar
			else fLcdWrite(GLCD_DATA, 1, xByte);
			xPos++;
			
			if (xPos < 64) fLcdWrite(GLCD_DATA, 0, xByte); // 1/3 of bar
			else fLcdWrite(GLCD_DATA, 1, xByte);
			xPos++;
			
			if (xPos < 64) fLcdWrite(GLCD_DATA, 0, xByte); // 1/3 of bar
			else fLcdWrite(GLCD_DATA, 1, xByte);
			xPos++;
			
			if (xPos < 64) fLcdWrite(GLCD_DATA, 0, 0x00); // gap
			else fLcdWrite(GLCD_DATA, 1, 0x00);
			xPos++;
		}
	}
}

// Initialise the gLCD
void gLcdInit(void)
{
	// Bring the display out of reset
	//GLCD_RES = 0; // Screen in reset
	__delay_us(250);
	//GLCD_RES = 1; // Screen out of reset
	__delay_us(250);

	// Set Y Address = 0
	fLcdWrite(GLCD_CMD, 0, 0b01000000);
	fLcdWrite(GLCD_CMD, 1, 0b01000000);

	// Set X Address = 0
	fLcdWrite(GLCD_CMD, 0, 0b10111000);
	fLcdWrite(GLCD_CMD, 1, 0b10111000);

	// Set Display start line = 0
	fLcdWrite(GLCD_CMD, 0, 0b11000000);
	fLcdWrite(GLCD_CMD, 1, 0b11000000);

	// Turn the display ON
	fLcdWrite(GLCD_CMD, 0, 0b00111111);
	fLcdWrite(GLCD_CMD, 1, 0b00111111);
}

// Clear the gLCD to black (zero)
void gLcdClear(void)
{
	unsigned char x, y;

	for (y = 0; y < 8; y++)
	{
		// Move to the correct screen page
		fLcdWrite(GLCD_CMD, 0, y | 0b10111000);
		fLcdWrite(GLCD_CMD, 0, 0b01000000);

		fLcdWrite(GLCD_CMD, 1, y | 0b10111000);
		fLcdWrite(GLCD_CMD, 1, 0b01000000);
		
		for (x = 0; x < 64; x++)
		{
			fLcdWrite(GLCD_DATA, 0, 0x00);
			fLcdWrite(GLCD_DATA, 1, 0x00);
		}
	}
}

#endif