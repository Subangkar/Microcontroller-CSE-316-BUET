#include <stdio.h>
#include <math.h>


#ifndef N_SAMPLE_POINTS
#define N_SAMPLE_POINTS 15
//#define N_SAMPLE_POINTS 7
#define SAMPLING_FREQ 20000 // 20KHz
#endif





#define PI2 6.283185
#define TIME_ARRAY xre
#define FREQ_MAG_ARRAY P
float xre[N_SAMPLE_POINTS];           // discrete-time signal, xre
float Pre[N_SAMPLE_POINTS], Pim[N_SAMPLE_POINTS]; // DFT of xre (real and imaginary parts)
float P[N_SAMPLE_POINTS];           // power spectrum of xre
float sin_table[N_SAMPLE_POINTS*N_SAMPLE_POINTS];
float cos_table[N_SAMPLE_POINTS*N_SAMPLE_POINTS];
int n, k;             // indices for time and frequency domains
void dft()
{
	// Calculate DFT of xre using brute force
	for (k=0 ; k<N_SAMPLE_POINTS ; ++k)
	{
		// Real part of X[k]
		Pre[k] = 0;
		// for (n=0 ; n<N_SAMPLE_POINTS ; ++n) Pre[k] += xre[n] * cos(n * k * PI2 / N_SAMPLE_POINTS);
		for (n=0 ; n<N_SAMPLE_POINTS ; ++n) Pre[k] += xre[n] * cos_table[n * k];
		
		// Imaginary part of X[k]
		Pim[k] = 0;
		// for (n=0 ; n<N_SAMPLE_POINTS ; ++n) Pim[k] -= xre[n] * sin(n * k * PI2 / N_SAMPLE_POINTS);
		for (n=0 ; n<N_SAMPLE_POINTS ; ++n) Pim[k] -= xre[n] * sin_table[n * k];
		
		// Power at kth frequency bin
		P[k] = Pre[k]*Pre[k] + Pim[k]*Pim[k];
	}
}

void initializeSinCosTable()
{
	for (k=0 ; k<N_SAMPLE_POINTS ; ++k)
	{
		for (n=0 ; n<N_SAMPLE_POINTS ; ++n){ 
            cos_table[n*k] = cos(n * k * PI2 / N_SAMPLE_POINTS);
            sin_table[n*k] = sin(n * k * PI2 / N_SAMPLE_POINTS);
        }
	}
}



double f(double t)
{
	return 2.5*sin(PI2*7000*t)+sin(PI2*8000*t)+2*sin(PI2*10000*t)+2.5*sin(PI2*3000*t)+1.5*cos(PI2*1500*t);
}



float sample_period;
int main()
{

    sample_period = 1/(float)SAMPLING_FREQ;

	for (n=0 ; n<N_SAMPLE_POINTS ; ++n) TIME_ARRAY[n] = f(sample_period*n);
    initializeSinCosTable();
    dft();

    // Output results to MATLAB / Octave M-file for plotting
    FILE *f = fopen("dftplots.m", "w");
    fprintf(f, "clear all\n", N_SAMPLE_POINTS-1);
   // fprintf(f, "n = [0:%d];\n", N_SAMPLE_POINTS-1);

    fprintf(f, "xre = [ ");
    for (n=0 ; n<N_SAMPLE_POINTS ; ++n) fprintf(f, "%f ", xre[n]);
    fprintf(f, "];\n");
    // fprintf(f, "Pre = [ ");
    // for (k=0 ; k<N_SAMPLE_POINTS ; ++k) fprintf(f, "%f ", Pre[k]);
    // fprintf(f, "];\n");
    // fprintf(f, "Pim = [ ");
    // for (k=0 ; k<N_SAMPLE_POINTS ; ++k) fprintf(f, "%f ", Pim[k]);
    // fprintf(f, "];\n");
    fprintf(f, "P = [ ");
    for (k=0 ; k<N_SAMPLE_POINTS ; ++k) fprintf(f, "%f ", P[k]);
    fprintf(f, "];\n");
    fprintf(f,"P=P/%d;\n",N_SAMPLE_POINTS);
    // fprintf(f,"P(2:end-1) = 2*P(2:end-1);\n");
    // fprintf(f, "subplot(3,1,1)\n");
    fprintf(f,"t = linspace(0,%f,%d);\n",sample_period,N_SAMPLE_POINTS); // Fs/2 ,L/2 
    fprintf(f,"f = linspace(0,%d,%d);\n",SAMPLING_FREQ/2,N_SAMPLE_POINTS/2+1); // Fs/2 ,L/2 
    fprintf(f,"figure(1)\n");
    fprintf(f,"plot(t,xre)\n");
    // fprintf(f, "xlim([0 %d])\n", N_SAMPLE_POINTS-1);
    // fprintf(f, "subplot(3,1,2)\nplot(n,Pre,n,Pim)\n");
    // fprintf(f, "xlim([0 %d])\n", N_SAMPLE_POINTS-1);
    // fprintf(f, "subplot(3,1,3)\nstem(n,P)\n");
    // fprintf(f, "xlim([0 %d])\n", N_SAMPLE_POINTS-1);
    fprintf(f,"figure(2)\n");
    fprintf(f,"plot(f,P(1:%d))\n",N_SAMPLE_POINTS/2+1);
    fclose(f);

    return 0;
}
