#include <stdio.h>
#include <math.h>


#ifndef N
#define N 128
#endif
#define PI2 6.2832


double f(double t)
{
	return sin(PI2*0.5*t)+sin(PI2*0.25*t);
}


float x[N];           // discrete-time signal, x
float Xre[N], Xim[N]; // DFT of x (real and imaginary parts)
float P[N];           // power spectrum of x
int n, k;             // indices for time and frequency domains

int dft()
{
	// time and frequency domain data arrays
	
	// Generate random discrete-time signal x in range (-1,+1)
	//srand(time(0));
	for (n=0 ; n<N ; ++n) x[n] = f(n);
	
	// Calculate DFT of x using brute force
	for (k=0 ; k<N ; ++k)
	{
		// Real part of X[k]
		Xre[k] = 0;
		for (n=0 ; n<N ; ++n) Xre[k] += x[n] * cos(n * k * PI2 / N);
		
		// Imaginary part of X[k]
		Xim[k] = 0;
		for (n=0 ; n<N ; ++n) Xim[k] -= x[n] * sin(n * k * PI2 / N);
		
		// Power at kth frequency bin
		P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
	}
    return 0;
}



int main()
{

    dft();

    // Output results to MATLAB / Octave M-file for plotting
    FILE *f = fopen("dftplots.m", "w");
    fprintf(f, "n = [0:%d];\n", N-1);
    fprintf(f, "x = [ ");
    for (n=0 ; n<N ; ++n) fprintf(f, "%f ", x[n]);
    fprintf(f, "];\n");
    // fprintf(f, "Xre = [ ");
    // for (k=0 ; k<N ; ++k) fprintf(f, "%f ", Xre[k]);
    // fprintf(f, "];\n");
    // fprintf(f, "Xim = [ ");
    // for (k=0 ; k<N ; ++k) fprintf(f, "%f ", Xim[k]);
    // fprintf(f, "];\n");
    fprintf(f, "P = [ ");
    for (k=0 ; k<N ; ++k) fprintf(f, "%f ", P[k]);
    fprintf(f, "];\n");
    // fprintf(f, "subplot(3,1,1)\n");
    fprintf(f,"plot(n,x)\n");
    // fprintf(f, "xlim([0 %d])\n", N-1);
    // fprintf(f, "subplot(3,1,2)\nplot(n,Xre,n,Xim)\n");
    // fprintf(f, "xlim([0 %d])\n", N-1);
    // fprintf(f, "subplot(3,1,3)\nstem(n,P)\n");
    // fprintf(f, "xlim([0 %d])\n", N-1);
    fprintf(f,"plot(n,P)\n");
    fclose(f);

    return 0;
}
