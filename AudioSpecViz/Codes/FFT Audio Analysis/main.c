/************************************************************************
	main.c

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

#ifndef MAIN_C
#define MAIN_C

// Global includes
#include <htc.h>
#include <stdio.h>

// Local includes
#include "hardware.h"
#include "fft.h"
#include "graph.h"

// PIC18F4550/PIC18F2550 fuse configuration:
// Config word 1 (Oscillator configuration)
// 20Mhz crystal input scaled to 48Mhz and configured for USB operation
__CONFIG(1, USBPLL & IESODIS & FCMDIS & HSPLL & CPUDIV1 & PLLDIV5);
// Config word 2
__CONFIG(2, VREGEN & PWRTDIS & BORDIS & BORV20 & WDTDIS & WDTPS32K);
// Config word 3
__CONFIG(3, PBDIGITAL & LPT1DIS & MCLREN);
// Config word 4
__CONFIG(4, XINSTDIS & STVREN & LVPDIS & ICPORTDIS & DEBUGDIS);
// Config word 5, 6 and 7 (protection configuration)
__CONFIG(5, UNPROTECT);
__CONFIG(6, UNPROTECT);
__CONFIG(7, UNPROTECT);

// Globals
short imaginaryNumbers[64];
short realNumbers[64];

void main(void)
{
	// PIC port set up --------------------------------------------------------

	// Configure on-board ADC
	// Vss and Vdd as voltage references
	ADCON1 = 0b00001110;

	// Configure the ADC acquisition time according to the datasheet
	ADCON2 = 0b10110110; // Note: output is right justified

	// Configure ports as inputs (1) or outputs(0)
	//        76543210
	TRISA = 0b00000001;
	TRISB = 0b00000000;
	TRISC = 0b00000011;
	TRISD = 0b00000000;
	TRISE = 0b00000000;

	// Clear all ports
	//        76543210
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;
	PORTE = 0b00000000;
	
	RE0 = 0;
	RE1 = 0;
	RE2 = 0;
	
	// Initialise the gLCD
	gLcdInit();
	gLcdClear();

	
	while(1)
	{
		// Perform the FFT

		// Get 64 samples at 50uS intervals
		// 50uS means our sampling rate is 20KHz which gives us
		// Nyquist limit of 10Khz
		short i = 0;
		unsigned short result;
		for (i = 0; i < 64; i++)
		{
			// Perform the ADC conversion
			// Select the desired ADC and start the conversion
			ADCON0 = 0b00000011; 	// Start the ADC conversion on AN0
		
			// Wait for the ADC conversion to complete
			TESTPIN_W4 = 1; // Don't remove this... it will affect the sample timing
			while(GODONE);
			TESTPIN_W4 = 0; // Don't remove this... it will affect the sample timing
			
			// Get the 10-bit ADC result and adjust the virtual ground of 2.5V
			// back to 0Vs to make the input wave centered correctly around 0
			// (i.e. -512 to +512)
			realNumbers[i] = ((short)(ADRESH << 8) + (short)ADRESL) - 512;
			
			// Set the imaginary number to zero
			imaginaryNumbers[i] = 0;
			
			// This delay is calibrated using an oscilloscope according to the 
			// output on RA1 to ensure that the sampling periods are correct
			// given the overhead of the rest of the code and the ADC sampling
			// time.
			//
			// If you change anything in this loop or use the professional 
			// (optimised) version of Hi-Tech PICC18, you will need to re-
			// calibrate this to achieve an accurate sampling rate.
			__delay_us(7);
		}

		// Perform the (forward) FFT calculation

		// Note: the FFT result length is half of the input data length
		// so if we put 64 samples in we get 32 buckets out.  The first bucket
		// cannot be used so in reality our result is 31 buckets.
		//
		// The maximum frequency we can measure is half of the sampling rate
		// so if we sample at 20Khz our maximum is 10Khz (this is called the 
		// Nyquist frequency).  So if we have 32 buckets divided over 10Khz,
		// each bucket represents 312.5Khz of range, so our lowest bucket is
		// (bucket 1) 312.5Hz - 625Hz and so on up to our 32nd bucket which
		// is 9687.5Hz - 10,000Hz
		
		//  1 : 312.5 - 625
		//  2 : 625 - 937.5
		//  3 : 937.5 - 1250
		//  4 : 1250 - 1562.5
		//  5 : 1562.5 - 1875
		//  6 : 1875 - 2187.5
		//  7 : 2187.5 - 2500
		//  8 : 2500 - 2812.5
		//  9 : 2812.5 - 3125
		// 10 : 3125 - 3437.5
		// 11 : 3437.5 - 3750
		// 12 : 3750 - 4062.5
		// 13 : 4062.5 - 4375
		// 14 : 4375 - 4687.5
		// 15 : 4687.5 - 5000
		// 16 : 5000 - 5312.5
		// 17 : 5312.5 - 5625
		// 18 : 5625 - 5937.5
		// 19 : 5937.5 - 6250
		// 20 : 6250 - 6562.5
		// 21 : 6562.5 - 6875
		// 22 : 6875 - 7187.5
		// 23 : 7187.5 - 7500
		// 24 : 7500 - 7812.5
		// 25 : 7812.5 - 8125
		// 26 : 8125 - 8437.5
		// 27 : 8437.5 - 8750
		// 28 : 8750 - 9062.5
		// 29 : 9062.5 - 9375
		// 30 : 9375 - 9687.5
		// 31 : 9687.5 - 10000
		
		// Note: the '6' is the size of the input data (2 to the power of 6 = 64)
		TESTPIN_W5 = 1;
		fix_fft(realNumbers, imaginaryNumbers, 6);
		
		// Take the absolute value of the FFT results
		
		// Note: The FFT routine returns 'complex' numbers which consist of
		// both a real and imaginary part.  To find the 'absolute' value
		// of the returned data we have to calculate the complex number's
		// distance from zero which requires a little pythagoras and therefore
		// a square-root calculation too.  Since the PIC has multiplication
		// hardware, only the square-root needs to be optimised.          
		long place, root;
        for (int k=0; k < 32; k++)
        {
	        realNumbers[k] = (realNumbers[k] * realNumbers[k] + 
                   imaginaryNumbers[k] * imaginaryNumbers[k]);
                   
            // Now we find the square root of realNumbers[k] using a very
            // fast (but compiler dependent) integer approximation:
            // (adapted from: http://www.codecodex.com/wiki/Calculate_an_integer_square_root)
            place = 0x40000000;
			root = 0;
			
			if (realNumbers[k] >= 0) // Ensure we don't have a negative number
			{
				while (place > realNumbers[k]) place = place >> 2; 
				
				while (place)  
				{  
					if (realNumbers[k] >= root + place)  
					{  
						realNumbers[k] -= root + place;  
						root += place * 2;  
					}  
					root = root >> 1;  
					place = place >> 2;  
				}
			}
			realNumbers[k] = root;
	    }
	    TESTPIN_W5 = 0;
	    
	    // Now we have 32 buckets of audio frequency data represented as
	    // linear intensity in realNumbers[]
	    //
	    // Since the maximum input value (in theory) to the SQRT function is
	    // 32767, the peak output at this stage is SQRT(32767) = 181.
	    
	    // Draw a bar graph of the FFT output data
	    TESTPIN_W6 = 1;
	    drawFftGraph(realNumbers);
	    TESTPIN_W6 = 0;
	}
}

#endif