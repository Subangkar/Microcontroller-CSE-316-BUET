#include<stdio.h>
#include<stdint.h>
#include<math.h>
#define N 32
#define N_SAMPLE_POINTS N
#define SAMPLING_FREQ 20000 // 20KHz
#define REAL 0
#define IMG 1


const int16_t cos_lookup[]= {
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

const int16_t sin_lookup[]= {
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


int32_t fx[N];
int32_t Fu[N/2][2];
int32_t P[N];
// mapped to int
void DFT()
{
	int16_t count,degree;
	uint8_t u,k;
	count = 0;
	for (u=0; u<N/2; u++) {
		for (k=0; k<N; k++) {
			degree = degree_lookup[count]*2;
			count++;
            // degree = u*k;
			Fu[u][REAL] +=  fx[k] * cos_lookup[degree];
			Fu[u][IMG] += -fx[k] * sin_lookup[degree];
		}
		Fu[u][REAL] /= N;
		Fu[u][REAL] /= 10000;
		Fu[u][IMG] /= N;
		Fu[u][IMG] /= 10000;
	}
 	for (u=1; u<N/2; u++) {
        if(Fu[u][0]<0)Fu[u][REAL]*=-1;
        if(Fu[u][1]<0)Fu[u][IMG]*=-1;
        P[u] = (Fu[u][REAL] + Fu[u][IMG])/4;//(uint8_t)
    }
}

#define PI2 6.283185307
int16_t f(double t)
{
    float fltVal = 1.5+2.5*sin(PI2*9500*t)+sin(PI2*7000*t)+2*sin(PI2*8000*t)+2.5*sin(PI2*9000*t)+2.5*sin(PI2*3000*t)+2.5*cos(PI2*1500*t);
    return (int16_t)(fltVal/0.01953125);
}

uint8_t lcd_buf1[16];
uint8_t lcd_buf2[16];
int main()
{
    float sample_period = 1/(float)SAMPLING_FREQ;

    uint8_t mag;
	int i;
    for(i=0;i<N;i++) {
        fx[i] = f(sample_period*i);
        // printf("%d ",fx[i]);
    }
    DFT();

    for(i = 1; i<N/2; i++) {
        // if(Fu[i][0]<0)Fu[i][REAL]*=-1;
        // if(Fu[i][1]<0)Fu[i][IMG]*=-1;
        // P[i] = mag = (uint8_t)(Fu[i][REAL] + Fu[i][IMG])/4;
        // if((mag)>7) {
        //     lcd_buf1[i] = (mag) - 7 - 1;
        //     if(lcd_buf1[i] > 7)
        //     lcd_buf1[i] = 7;
        //     lcd_buf2[i] = 7;
        // }
        // else {
        //     lcd_buf1[i] = ' ';
        //     lcd_buf2[i] = mag;
        // }
    }
    int n,k;
    // Output results to MATLAB / Octave M-file for plotting
    FILE *f = fopen("dftVinu.m", "w");
    fprintf(f, "clear all\n");
   // fprintf(f, "n = [0:%d];\n", N_SAMPLE_POINTS-1);
    fprintf(f, "xre = [ ");
    for (n=0 ; n<N_SAMPLE_POINTS ; ++n) fprintf(f, "%d ", fx[n]);
    fprintf(f, "];\n");

    // fprintf(f, "Pre = [ ");
    // for (k=0 ; k<N_SAMPLE_POINTS ; ++k) fprintf(f, "%f ", Pre[k]);
    // fprintf(f, "];\n");
    // fprintf(f, "Pim = [ ");
    // for (k=0 ; k<N_SAMPLE_POINTS ; ++k) fprintf(f, "%f ", Pim[k]);
    // fprintf(f, "];\n");
    fprintf(f, "P = [ ");
    for (k=0 ; k<N_SAMPLE_POINTS ; ++k) fprintf(f, "%d ", P[k]);
    fprintf(f, "];\n");
    // fprintf(f,"P=P/%d;\n",N_SAMPLE_POINTS);
    // fprintf(f,"P(2:end-1) = 2*P(2:end-1);\n");
    // fprintf(f, "subplot(3,1,1)\n");
    fprintf(f,"t = linspace(0,%f,%d);\n",sample_period,N_SAMPLE_POINTS); // Fs/2 ,L/2 
    fprintf(f,"f = linspace(0,%d,%d);\n",SAMPLING_FREQ/2,N_SAMPLE_POINTS/2+1); // Fs/2 ,L/2 
    fprintf(f,"figure(1)\n");
    fprintf(f,"plot(t,xre)\n");
    fprintf(f,"figure(2)\n");
    fprintf(f,"plot(f,P(1:%d))\n",N_SAMPLE_POINTS/2+1);
    fclose(f);


    return 0;
}
