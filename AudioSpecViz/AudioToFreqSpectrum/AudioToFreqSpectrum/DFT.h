///*
 //* DFT.h
 //*
 //* Created: 16-Jul-18 9:39:07 AM
 //*  Author: SubangkarKr
 //*/ 
//
//
//#ifndef DFT_H_
//#define DFT_H_
//
//#ifndef N
//#define N 7
//#endif
//#ifndef N_SAMPLE_POINTS
//#define N_SAMPLE_POINTS 15
//#endif
//#ifndef PI2
//#define PI2 6.283185
//#endif
//
//#define TIME_ARRAY analogTimeBuff
//#define FREQ_MAG_ARRAY P
//float analogTimeBuff[N_SAMPLE_POINTS];           // discrete-time signal, xre
//float Pre[N_SAMPLE_POINTS], Pim[N_SAMPLE_POINTS]; // DFT of xre (real and imaginary parts)
//float P[N_SAMPLE_POINTS];           // power spectrum of xre
//float sin_table[N_SAMPLE_POINTS*N_SAMPLE_POINTS];
//float cos_table[N_SAMPLE_POINTS*N_SAMPLE_POINTS];
//int n, k;             // indices for time and frequency domains
//void dft()
//{
	//// Calculate DFT of xre using brute force
	//for (k=0 ; k<N_SAMPLE_POINTS ; ++k)
	//{
		//// Real part of X[k]
		//Pre[k] = 0;
		//for (n=0 ; n<N_SAMPLE_POINTS ; ++n) Pre[k] += analogTimeBuff[n] * cos_table[n * k];
		//
		//// Imaginary part of X[k]
		//Pim[k] = 0;
		//for (n=0 ; n<N_SAMPLE_POINTS ; ++n) Pim[k] -= analogTimeBuff[n] * sin_table[n * k];
		//
		//// Power at kth frequency bin
		//P[k] = Pre[k]*Pre[k] + Pim[k]*Pim[k];
	//}
//}
//
//void initializeSinCosTable()
//{
	//for (k=0 ; k<N_SAMPLE_POINTS ; ++k)
	//{
		//for (n=0 ; n<N_SAMPLE_POINTS ; ++n){
			//cos_table[n*k] = cos(n * k * PI2 / N_SAMPLE_POINTS);
			//sin_table[n*k] = sin(n * k * PI2 / N_SAMPLE_POINTS);
		//}
	//}
//}
//
//
////#endif /* DFT_H_ */