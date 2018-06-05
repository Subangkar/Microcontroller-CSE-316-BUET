/************************************************************************
	hardware.h

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

#ifndef _HARDWARE_H_
#define _HARDWARE_H_

// Fosc frequency (48 Mhz)
#define _XTAL_FREQ 48000000

#define OFF		0
#define ON		1
#define TOGGLE	2

#define TRUE	1
#define FALSE	0

#define READ	1
#define WRITE	0

// Hardware mapping definitions
// gLCD character display hardware
#define	GLCD_DB0			RD0
#define GLCD_DB1			RD1
#define GLCD_DB2			RD2
#define GLCD_DB3			RD3
#define	GLCD_DB4			RD4
#define GLCD_DB5			RD5
#define GLCD_DB6			RD6
#define GLCD_DB7			RD7

#define GLCD_DATABUS		PORTD
#define GLCD_DATADIRECTION	TRISD

#define GLCD_RS				RB0
#define GLCD_RW				RB1
#define GLCD_EN				RB2

#define GLCD_CS1			RB3
#define GLCD_CS2			RB4

#define LED0				RE0
#define LED1				RE1
#define LED2				RE2

#define TESTPIN_W4			RA1
#define TESTPIN_W5			RA2
#define TESTPIN_W6			RA3

#define SWITCH0				RC0
#define SWITCH1				RC1

#endif