/************************************************************************
	graph.h

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

#ifndef _GRAPH_H_
#define _GRAPH_H_

// This table is used to convert the FFT output range of 0-181 to the 
// display's Y resolution of 64 pixels using a linear scale.
const unsigned char linTable[182] = 
{
	0, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8,
	8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14,
	14, 15, 15, 15, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20,
	20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 25, 25, 25, 26, 26,
	26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32,
	32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38,
	38, 38, 39, 39, 39, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 44,
	44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 49, 49, 49, 50,
	50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55,
	56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 61,
	62, 62, 62, 63, 63, 63	
};

// This table is used to convert the FFT output range of 0-181 to the
// display's Y resolution of 64 pixels using a logarithmic scale.
// Note: this table is based on a 'dB' conversion of a = 18.1 * log(x/181)
// with some shifting to prevent the noise-floor being displayed.  It's 
// basically useless for audio analysis, but makes for a nice looking
// output :)
const unsigned char logTable[182] = 
{
	0, 0, 22, 27, 30, 33, 34, 36, 37, 38, 39, 40, 40, 41, 42, 42, 43, 43,
	44, 44, 45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49,
	49, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52,
	53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55,
	55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
	57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58,
	58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59,
	59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
	60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61,
	61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62,
	62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63
};

// This define states the delay when strobing the EN
// line in uS
#define ENSTROBEDELAY 10

// gLCD definitions
#define GLCD_READ			0b11111111
#define GLCD_WRITE			0b00000000
#define GLCD_CMD			0
#define GLCD_DATA			1

// Function prototypes
void drawFftGraph(short inputData[]);
void gLcdInit(void);
void gLcdClear(void);

#endif