/*
 * DFT.h
 *
 * Created: 16-Jul-18 9:39:07 AM
 *  Author: SubangkarKr
 */ 


#ifndef DFT_H_
#define DFT_H_

#ifndef
#define N 7
#endif
#define PI2 6.2832


double f(int t)
{
	return sin(PI2*100*t);
}

int dft()
{
	// time and frequency domain data arrays
	int n, k;             // indices for time and frequency domains
	float x[N];           // discrete-time signal, x
	float Xre[N], Xim[N]; // DFT of x (real and imaginary parts)
	float P[N];           // power spectrum of x
	
	// Generate random discrete-time signal x in range (-1,+1)
	//srand(time(0));
	for (n=0 ; n<N ; ++n) x[n] = ((2.0 * rand()) / RAND_MAX) - 1.0;
	
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

}

#endif /* DFT_H_ */