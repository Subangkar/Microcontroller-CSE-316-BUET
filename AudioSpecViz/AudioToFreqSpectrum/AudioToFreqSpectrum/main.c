/*
* AudioToFreqSpectrum.c
*
* Created: 15-Jul-18 8:30:23 PM
* Author : SubangkarKr
*/



//#ifndef F_CPU
//#define F_CPU 500000UL // 1 MHz clock speed
#define F_CPU 1000000UL // 1 MHz clock speed
//#define F_CPU 8000000UL // 8 MHz clock speed
//#endif

#include "Basic.h"
#define LCD_BUFFER_SIZE 30
char lcdStringBuff[LCD_BUFFER_SIZE];



int32_t maxV=0,minV=1023;



#define N_SAMPLE_POINTS 32
#define SAMPLING_FREQ 16000//8000 // 8KHz
#define OFFSET_DC_10BIT 327 // 1.6v
#define OFFSET_DC_8BIT 81 // 1.6v

#define SAMPLING_PERIOD 62//125 // 1Mhz clock 8khz sampling Period 1M/8k = 125us // timer'll inc every 1/1M = 1us
#define SAMPLING_SLEEP_CYCLE 52//105
#define ADC_PERIOD 52 // 13*4 @ 4us per cycle

//int analogTimeBuff[N_SAMPLE_POINTS];
//#define PI2 6.283185
int analogValue;
uint8_t analogBuffIndex;
#define TIME_AMP_ARRAY analogTimeBuff
#define FREQ_MAG_ARRAY P

#define REAL 0
#define IMG 1
const int16_t cos_lookup[] PROGMEM = {
	10000,9998,9993,9986,9975,9961,9945,9925,9902,
	9876,9848,9816,9781,9743,9702,9659,9612,9563,
	9510,9455,9396,9335,9271,9205,9135,9063,8987,
	8910,8829,8746,8660,8571,8480,8386,8290,8191,
	8090,7986,7880,7771,7660,7547,7431,7313,7193,
	7071,6946,6819,6691,6560,6427,6293,6156,6018,
	5877,5735,5591,5446,5299,5150,5000,4848,4694,
	4539,4383,4226,4067,3907,3746,3583,3420,3255,
	3090,2923,2756,2588,2419,2249,2079,1908,1736,
	1564,1391,1218,1045,871,697,523,348,174,
	0,-174,-348,-523,-697,-871,-1045,-1218,-1391,
	-1564,-1736,-1908,-2079,-2249,-2419,-2588,-2756,-2923,
	-3090,-3255,-3420,-3583,-3746,-3907,-4067,-4226,-4383,
	-4539,-4694,-4848,-4999,-5150,-5299,-5446,-5591,-5735,
	-5877,-6018,-6156,-6293,-6427,-6560,-6691,-6819,-6946,
	-7071,-7193,-7313,-7431,-7547,-7660,-7771,-7880,-7986,
	-8090,-8191,-8290,-8386,-8480,-8571,-8660,-8746,-8829,
	-8910,-8987,-9063,-9135,-9205,-9271,-9335,-9396,-9455,
	-9510,-9563,-9612,-9659,-9702,-9743,-9781,-9816,-9848,
	-9876,-9902,-9925,-9945,-9961,-9975,-9986,-9993,-9998,
	-10000,-9998,-9993,-9986,-9975,-9961,-9945,-9925,-9902,
	-9876,-9848,-9816,-9781,-9743,-9702,-9659,-9612,-9563,
	-9510,-9455,-9396,-9335,-9271,-9205,-9135,-9063,-8987,
	-8910,-8829,-8746,-8660,-8571,-8480,-8386,-8290,-8191,
	-8090,-7986,-7880,-7771,-7660,-7547,-7431,-7313,-7193,
	-7071,-6946,-6819,-6691,-6560,-6427,-6293,-6156,-6018,
	-5877,-5735,-5591,-5446,-5299,-5150,-5000,-4848,-4694,
	-4539,-4383,-4226,-4067,-3907,-3746,-3583,-3420,-3255,
	-3090,-2923,-2756,-2588,-2419,-2249,-2079,-1908,-1736,
	-1564,-1391,-1218,-1045,-871,-697,-523,-348,-174,
	0,174,348,523,697,871,1045,1218,1391,
	1564,1736,1908,2079,2249,2419,2588,2756,2923,
	3090,3255,3420,3583,3746,3907,4067,4226,4383,
	4539,4694,4848,5000,5150,5299,5446,5591,5735,
	5877,6018,6156,6293,6427,6560,6691,6819,6946,
	7071,7193,7313,7431,7547,7660,7771,7880,7986,
	8090,8191,8290,8386,8480,8571,8660,8746,8829,
	8910,8987,9063,9135,9205,9271,9335,9396,9455,
	9510,9563,9612,9659,9702,9743,9781,9816,9848,
	9876,9902,9925,9945,9961,9975,9986,9993,9998
};

const int16_t sin_lookup[] PROGMEM= {
	0,174,348,523,697,871,1045,1218,1391,
	1564,1736,1908,2079,2249,2419,2588,2756,2923,
	3090,3255,3420,3583,3746,3907,4067,4226,4383,
	4539,4694,4848,4999,5150,5299,5446,5591,5735,
	5877,6018,6156,6293,6427,6560,6691,6819,6946,
	7071,7193,7313,7431,7547,7660,7771,7880,7986,
	8090,8191,8290,8386,8480,8571,8660,8746,8829,
	8910,8987,9063,9135,9205,9271,9335,9396,9455,
	9510,9563,9612,9659,9702,9743,9781,9816,9848,
	9876,9902,9925,9945,9961,9975,9986,9993,9998,
	10000,9998,9993,9986,9975,9961,9945,9925,9902,
	9876,9848,9816,9781,9743,9702,9659,9612,9563,
	9510,9455,9396,9335,9271,9205,9135,9063,8987,
	8910,8829,8746,8660,8571,8480,8386,8290,8191,
	8090,7986,7880,7771,7660,7547,7431,7313,7193,
	7071,6946,6819,6691,6560,6427,6293,6156,6018,
	5877,5735,5591,5446,5299,5150,4999,4848,4694,
	4539,4383,4226,4067,3907,3746,3583,3420,3255,
	3090,2923,2756,2588,2419,2249,2079,1908,1736,
	1564,1391,1218,1045,871,697,523,348,174,
	0,-174,-348,-523,-697,-871,-1045,-1218,-1391,
	-1564,-1736,-1908,-2079,-2249,-2419,-2588,-2756,-2923,
	-3090,-3255,-3420,-3583,-3746,-3907,-4067,-4226,-4383,
	-4539,-4694,-4848,-4999,-5150,-5299,-5446,-5591,-5735,
	-5877,-6018,-6156,-6293,-6427,-6560,-6691,-6819,-6946,
	-7071,-7193,-7313,-7431,-7547,-7660,-7771,-7880,-7986,
	-8090,-8191,-8290,-8386,-8480,-8571,-8660,-8746,-8829,
	-8910,-8987,-9063,-9135,-9205,-9271,-9335,-9396,-9455,
	-9510,-9563,-9612,-9659,-9702,-9743,-9781,-9816,-9848,
	-9876,-9902,-9925,-9945,-9961,-9975,-9986,-9993,-9998,
	-10000,-9998,-9993,-9986,-9975,-9961,-9945,-9925,-9902,
	-9876,-9848,-9816,-9781,-9743,-9702,-9659,-9612,-9563,
	-9510,-9455,-9396,-9335,-9271,-9205,-9135,-9063,-8987,
	-8910,-8829,-8746,-8660,-8571,-8480,-8386,-8290,-8191,
	-8090,-7986,-7880,-7771,-7660,-7547,-7431,-7313,-7193,
	-7071,-6946,-6819,-6691,-6560,-6427,-6293,-6156,-6018,
	-5877,-5735,-5591,-5446,-5299,-5150,-5000,-4848,-4694,
	-4539,-4383,-4226,-4067,-3907,-3746,-3583,-3420,-3255,
	-3090,-2923,-2756,-2588,-2419,-2249,-2079,-1908,-1736,
	-1564,-1391,-1218,-1045,-871,-697,-523,-348,-174
};

const uint8_t degree_lookup[]= {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,5,11,16,22,28,33,39,45,50,56,61,67,
	73,78,84,90,95,101,106,112,118,123,129,135,140,146,151,
	157,163,168,174,0,11,22,33,45,56,67,78,90,101,112,
	123,135,146,157,168,0,11,22,33,44,56,67,78,90,101,
	112,123,134,146,157,168,0,16,33,50,67,84,101,118,135,
	151,168,5,22,39,56,73,90,106,123,140,157,174,11,28,
	45,61,78,95,112,129,146,163,0,22,45,67,90,112,135,
	157,0,22,44,67,90,112,134,157,0,22,45,67,89,112,
	134,157,0,22,45,67,89,112,135,157,0,28,56,84,112,
	140,168,16,44,73,101,129,157,5,33,61,89,118,146,174,
	22,50,78,106,135,163,11,39,67,95,123,151,0,33,67,
	101,135,168,22,56,90,123,157,11,45,78,112,146,0,33,
	67,101,135,168,22,56,90,123,157,11,44,78,112,146,0,
	39,78,118,157,16,56,95,134,174,33,73,112,151,11,50,
	89,129,168,28,67,106,146,5,44,84,123,163,22,61,101,
	140,0,45,90,135,0,44,90,134,0,45,89,134,0,45,
	89,135,0,44,90,135,179,44,89,134,0,45,90,134,179,
	44,90,135,0,50,101,151,22,73,123,174,45,95,146,16,
	67,118,168,39,90,140,11,61,112,163,33,84,134,5,56,
	106,157,28,78,129,0,56,112,168,44,101,157,33,89,146,
	22,78,135,11,67,123,179,56,112,168,45,101,157,33,90,
	146,22,78,134,11,67,123,0,61,123,5,67,129,11,73,
	134,16,78,140,22,84,146,28,89,151,33,95,157,39,101,
	163,44,106,168,50,112,174,56,118,0,67,135,22,90,157,
	45,112,0,67,135,22,90,157,44,112,0,67,134,22,90,
	157,44,112,0,67,134,22,89,157,45,112,0,73,146,39,
	112,5,78,151,45,118,11,84,157,50,123,16,90,163,56,
	129,22,95,168,61,134,28,101,174,67,140,33,106,0,78,
	157,56,134,33,112,11,89,168,67,146,44,123,22,101,179,
	78,157,56,134,33,112,11,89,168,67,146,44,123,22,101,
	0,84,168,73,157,61,146,50,135,39,123,28,112,16,101,
	5,90,174,78,163,67,151,56,140,45,129,33,118,22,106,
	11,95
};

int32_t analogTimeBuff[N_SAMPLE_POINTS];
int32_t Pc[N_SAMPLE_POINTS/2][2];
int32_t P[N_SAMPLE_POINTS];
// mapped to int
void DFT()
{
	int16_t count,degree;
	uint8_t u,k;
	count = 0;
	for (u=0; u<N_SAMPLE_POINTS/2; u++) {
		for (k=0; k<N_SAMPLE_POINTS; k++) {
			degree = degree_lookup[count]*2;
			count++;
			//			Pc[u][REAL] +=  analogTimeBuff[k] * cos_lookup[degree];
			//			Pc[u][IMG]	+= -analogTimeBuff[k] * sin_lookup[degree];
			Pc[u][REAL] +=  analogTimeBuff[k] * pgm_read_word(&cos_lookup[degree]);
			Pc[u][IMG]	+= -analogTimeBuff[k] * pgm_read_word(&sin_lookup[degree]);
		}
		Pc[u][REAL] /= N_SAMPLE_POINTS;
		Pc[u][REAL] /= 10000;
		Pc[u][IMG] /= N_SAMPLE_POINTS;
		Pc[u][IMG] /= 10000;
	}
	for (u=1; u<N_SAMPLE_POINTS/2; u++) {
		if(Pc[u][0]<0)Pc[u][REAL]*=-1;
		if(Pc[u][1]<0)Pc[u][IMG]*=-1;
		P[u] = (Pc[u][REAL] + Pc[u][IMG])/4;//(uint8_t)
		if(P[u]<minV) minV = P[u]; // && P[u]
		if(P[u]>maxV) maxV = P[u];
	}
}




//ISR(TIMER1_COMPB_vect, ISR_NAKED)
//{
//sei();
//sleep_cpu();
//reti();
//}

uint16_t readAnalogValue(uint8_t res);
//ISR (TIMER1_COMPA_vect) {
//if(analogBuffIndex<N_SAMPLE_POINTS) {
////while(ADCSRA&(1<<ADSC));
//analogTimeBuff[analogBuffIndex++]=readAnalogValue(8);//-OFFSET_DC_8BIT;
////		if(analogTimeBuff[analogBuffIndex-1]>maxV) maxV = analogTimeBuff[analogBuffIndex-1];
////		if(analogTimeBuff[analogBuffIndex-1]<minV) minV = analogTimeBuff[analogBuffIndex-1];
//
////Lcd8_Clear();
////Lcd8_Set_Cursor(1,0);
////sprintf(lcdStringBuff,"val : %ld",analogTimeBuff[analogBuffIndex-1]);
////sprintf(lcdStringBuff,"%u",analogBuffIndex);
////Lcd8_Write_String(lcdStringBuff);
//
//// must be removed
////_delay_us(10);// to show diff of voltages with time
//}
//}


int adcCycDur=0;
void adcConfig()
{
	ADMUX = (((0<<REFS1)|(1<<REFS0)|(1<<ADLAR))+0);
	ADCSRA =  (1<<ADEN)+2;//3;//prescaler=3 : div=8
	
	// let max audio frequency = 4kHz
	// sampling frequency = 8kHz => time = 125us = max_time to get adc value
	// with prescaler = 3 && sys clock = 1MHz
	// adc clock = 1M/8 = 125KHz
	// adc sample Freq = 125/13 = 9KHz => time_req = 104us < sampling, hence ok
}

void timerConfig(){
	OCR1A = SAMPLING_PERIOD;
	//OCR1B = SAMPLING_SLEEP_CYCLE;
	TCCR1A = 0;
	TCCR1B = (1<<WGM12) | (1<<CS10);
	//TIMSK = (1<<OCIE1A)|(1<<OCIE1B);
	//TIMSK = 0;
}


void initDataTables()
{
	analogBuffIndex=0;
	//initializeSinCosTable();
	int i;
	forLoop(i,N_SAMPLE_POINTS)
	{
		TIME_AMP_ARRAY[i]=0;
		FREQ_MAG_ARRAY[i]=0;
	}
}

uint16_t readAnalogValue(uint8_t res)
{
	//adcCycDur=TCNT1;
	while(ADCSRA&(1<<ADSC));
	//adcCycDur=TCNT1-adcCycDur;
	analogValue = ADCL;
	if(res==10)
	analogValue = (analogValue>>6)|(ADCH<<2);
	else
	analogValue = ADCH;
	//ADCSRA |= (1<<ADSC);// start conversion
	return analogValue;
}



#define SPEC_BIN_MAG_ARRAY specBinBuf
int16_t specBinBuf[N_SAMPLE_POINTS/2];

#define PRINT_ARRAY FREQ_MAG_ARRAY
#define PRINT_ARRAY_STEP 2


void Sampling()
{
	TCNT1 = 0;
	TIFR |= 1<<OCF1A;
	for(analogBuffIndex=0;analogBuffIndex<N_SAMPLE_POINTS;analogBuffIndex++) {
		ADCSRA |= (1<<ADSC);
		while((TIFR & (1<<OCF1A)) == 0);
		TIME_AMP_ARRAY[analogBuffIndex] = readAnalogValue(8);
		TIFR |= 1<<OCF1A;
	}
}

void Spectrum()
{
	int i;
	int i1,i2;
	forLoop(i,N_SAMPLE_POINTS/2)
	{
		i1 = 2*i;
		i2 = i1+1;
		SPEC_BIN_MAG_ARRAY[i] = ((FREQ_MAG_ARRAY[i1]+FREQ_MAG_ARRAY[i2])/2)-150;
		if(SPEC_BIN_MAG_ARRAY[i]<0) SPEC_BIN_MAG_ARRAY[i]=0;
	}
	
	Lcd8_Set_Cursor(1,0);
	sprintf(lcdStringBuff,"%ld %ld %ld %ld",PRINT_ARRAY[0],PRINT_ARRAY[1*PRINT_ARRAY_STEP],PRINT_ARRAY[2*PRINT_ARRAY_STEP],PRINT_ARRAY[3*PRINT_ARRAY_STEP]);//"%d %d %d %d" //"%ld %ld %ld %ld"
	Lcd8_Write_String(lcdStringBuff);

	Lcd8_Set_Cursor(2,0);
	sprintf(lcdStringBuff,"%ld %ld %ld %ld",PRINT_ARRAY[4*PRINT_ARRAY_STEP],PRINT_ARRAY[5*PRINT_ARRAY_STEP],PRINT_ARRAY[6*PRINT_ARRAY_STEP],PRINT_ARRAY[7*PRINT_ARRAY_STEP]);
	Lcd8_Write_String(lcdStringBuff);
	
	Lcd8_Set_Cursor(1,0);
	sprintf(lcdStringBuff,"MAX : %ld  %ld",maxV,analogTimeBuff[0]);
	//Lcd8_Write_String(lcdStringBuff);
	Lcd8_Set_Cursor(2,0);
	sprintf(lcdStringBuff,"MIN : %ld  %ld",minV,analogTimeBuff[7]);
	//Lcd8_Write_String(lcdStringBuff);

}

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;


	
	adcConfig();
	timerConfig();
	Lcd8_Init();
	initDataTables();
	//sei();
	//set_sleep_mode(SLEEP_MODE_IDLE);
	//sleep_enable();
	while(1)
	{

		Sampling();
		Lcd8_Clear();
		//Lcd8_Set_Cursor(1,0);
		//Lcd8_Write_String("Here");
		
		//if(analogBuffIndex==N_SAMPLE_POINTS)
		//{
		DFT();
		
		Spectrum();
		//			analogBuffIndex=0;
		_delay_ms(750);
		//}
		//TCNT1=0;//reset the timer for next time
	}

}

