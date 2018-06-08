#include <iostream>
#include<math.h>

#define PI 3.14159265

using namespace std;

//---Class for manipulating complex numbers.
class Complex
{
public:
    double real;
    double img;
    Complex()
    {
        real=img=0;
    }
    Complex (int r, int i)
    {
        real=r;
        img=i;
    }
    Complex operator+(Complex op)
    {
        Complex temp;
        temp.real=this->real+op.real;
        temp.img=this->img+op.img;
        return temp;
    }
    Complex operator-(Complex op)
    {
        Complex temp;
        temp.real=this->real-op.real;
        temp.img=this->img-op.img;
        return temp;
    }
    Complex operator*(Complex op)
    {
        Complex temp;
        temp.real=this->real*op.real-this->img*op.img;
        temp.img=this->real*op.img+this->img*op.real;
        return temp;
    }
    friend ostream & operator<<(ostream & os, Complex c)
    {
        os<<c.real<<(c.img>=0 ? "+":"")<<c.img<<"j";
        return os;
    }
};

//---Twiddle factor calculation
Complex twiddle_factor(int N, int k)
{
    Complex omp;
    omp.real=cos(2*k*PI/N);
    omp.img=-sin(2*k*PI/N);
    return omp;
}

//-----Bit reversal routine.
void bitReversal(Complex *g, int N)
{
    for (int i=0; i<N/2; i++)
    {
        int index=i;
        int cIndex=0;
        for (int j=1; j<N; j=j*2)
        {
            cIndex=cIndex*2+index%2;
            index=index/2;
        }
        Complex temp=g[i];
        g[i]=g[cIndex];
        g[cIndex]=temp;
    }
}

//-----Discrete Fourier Transform (DFT). O(N^2).
void DFT(Complex* g, Complex* G, int N)
{
    for (int k=0; k<N; k++)
    {
        G[k].real=G[k].img=0;
        for (int n=0; n<N; n++)
        {
            G[k]=G[k]+g[n]*twiddle_factor(N,k*n);
        }

    }
}
//-----Recursive FFT. Decimation-in-frequency.
void DIF_FFT(Complex* g, Complex* G, int N)
{
    if (N==2)
    {
        G[0]=g[0]+g[1];
        G[1]=g[0]-g[1];
        return;
    }
    Complex x[N/2];
    Complex y[N/2];

    for (int i=0; i<N/2; i++)
    {
        x[i]=g[i]+g[i+N/2];
        y[i]=(g[i]-g[i+N/2])*twiddle_factor(N,i);
    }
    DIF_FFT(x,G,N/2);
    DIF_FFT(y,&G[N/2],N/2);

}

//-----Recursive FFT in place. Decimation-in-frequency.
void DIF_FFT_IP(Complex* g, int N)
{
    if (N==2)
    {
        Complex temp=g[0]-g[1];
        g[0]=g[0]+g[1];
        g[1]=temp;
        return;
    }

    for (int i=0; i<N/2; i++)
    {
        Complex temp=g[i]-g[i+N/2];
        g[i]=g[i]+g[i+N/2];
        g[i+N/2]=(temp)*twiddle_factor(N,i);
    }
    DIF_FFT_IP(g,N/2);
    DIF_FFT_IP(&g[N/2],N/2);
}

//-----Non-Recursive FFT. Decimation-in-frequency
void DIF_FFT_NR(Complex* g, int N)
{
    int stages=log(N)/log(2);
    int size_Block_CurrentStage=N;

    for (int k=0; k<stages; k++)
    {
        int size_Block_NextStage=size_Block_CurrentStage/2;

        for (int j=0; j<size_Block_NextStage; j++)
        {
            for (int i=j; i<N; i=i+size_Block_CurrentStage)
            {
                int kk=i+size_Block_NextStage;
                Complex temp=g[i];
                g[i]=g[i]+g[kk];
                g[kk]=(temp-g[kk])*twiddle_factor(size_Block_CurrentStage,j);
            }
        }
        size_Block_CurrentStage=size_Block_NextStage;
    }
}

//-----Recursive FFT. Decimation-in-time.
void DIT_FFT(Complex* g, Complex* G, int N)
{
    if (N==2)
    {
        G[0]=g[0]+g[1];
        G[1]=g[0]-g[1];
        return;
    }
    Complex even[N/2];
    Complex odd[N/2];

    for (int i=0; i<N/2; i++)
    {
        even[i]=g[2*i];
        odd[i]=g[2*i+1];
    }
    DIT_FFT(even,G,N/2);
    DIT_FFT(odd,&G[N/2],N/2);

    for (int i=0; i<N/2; i++)
    {
        Complex temp=G[i];
        G[i]=G[i]+twiddle_factor(N,i)*G[i+N/2];
        G[i+N/2]=temp-twiddle_factor(N,i)*G[i+N/2];
    }
}
//-----Recursive FFT in place. Decimation-in-time.
void DIT_FFT_IP(Complex* g, int N)
{
    if (N==2)
    {
        Complex temp=g[0];
        g[0]=g[0]+g[1];
        g[1]=temp-g[1];
        return;
    }

    DIT_FFT_IP(g,N/2);
    DIT_FFT_IP(&g[N/2],N/2);

    for (int i=0; i<N/2; i++)
    {
        Complex temp=g[i];
        g[i]=g[i]+twiddle_factor(N,i)*g[i+N/2];
        g[i+N/2]=temp-twiddle_factor(N,i)*g[i+N/2];
    }
}

//-----Non-Recursive FFT. Decimation-in-time
void DIT_FFT_NR(Complex* g, int N)
{
    int stages=log(N)/log(2);
    int size_Block_PrevStage=1;

    for (int k=0; k<stages; k++)
    {
        int size_Block_CurrentStage=size_Block_PrevStage*2;

        for (int j=0; j<size_Block_PrevStage; j++)
        {
            for (int i=j; i<N; i=i+size_Block_CurrentStage)
            {
                int kk=i+size_Block_PrevStage;
                Complex temp=g[i];
                g[i]=g[i]+twiddle_factor(size_Block_CurrentStage,j)*g[kk];
                g[kk]=temp-twiddle_factor(size_Block_CurrentStage,j)*g[kk];
            }
        }
        size_Block_PrevStage=size_Block_CurrentStage;
    }
}
//----main function
int main()
{
    while(1)
    {
        int N=8; //should always be a power of 2.
        Complex g[N];

        //input section.
        for (int i=0; i<N; i++)
        {
            g[i].real=i+1;
        }
        //--end of input

        cout<<"1. DFT O(N^2). 2. Recursive FFT (DIF). 3. Recursive FFT in place (DIF). 4. Non-Recursive FFT (DIF).\n";
        cout<<"5. Recursive FFT (DIT). 6. Recursive FFT in place (DIT). 7. Non-Recursive FFT (DIT). 8. Exit\n";

        int ch;
        cin>>ch;

        //--Choice: Recursive FFT (Decimation-in-frequency)
        if(ch==1)
        {
            Complex G[N];
            DFT(g,G,N);
            for (int i=0; i<N; i++)
            {
                cout<<G[i]<<endl;
            }
        }
        //--Choice: Recursive FFT (Decimation-in-frequency)
        else if(ch==2)
        {
            Complex G[N];
            DIF_FFT(g,G,N);
            bitReversal(G,N); //bit reversal
            for (int i=0; i<N; i++)
            {
                cout<<G[i]<<endl;
            }
        }
        //--Choice: Recursive FFT in place (Decimation-in-frequency)
        else if(ch==3)
        {
            DIF_FFT_IP(g,N);
            bitReversal(g,N);  //bit reversal
            for (int i=0; i<N; i++)
            {
                cout<<g[i]<<endl;
            }

        }
        //--Choice: Non-Recursive FFT (Decimation-in-frequency)
        else if(ch==4)
        {
            DIF_FFT_NR(g,N);
            bitReversal(g,N);  //bit reversal
            for (int i=0; i<N; i++)
            {
                cout<<g[i]<<endl;
            }
        }
        //--Choice: Recursive FFT (Decimation-in-time)
        if(ch==5)
        {
            Complex G[N];
            DIT_FFT(g,G,N);

            for (int i=0; i<N; i++)
            {
                cout<<G[i]<<endl;
            }
        }
        //--Choice: Recursive FFT in place (Decimation-in-time)
        if(ch==6)
        {
            bitReversal(g,N); //bit reversal
            DIT_FFT_IP(g,N);

            for (int i=0; i<N; i++)
            {
                cout<<g[i]<<endl;
            }
        }
        //--Choice: Non-Recursive FFT (Decimation-in-frequency)
        else if(ch==7)
        {
            bitReversal(g,N); //bit reversal
            DIT_FFT_NR(g,N);
            for (int i=0; i<N; i++)
            {
                cout<<g[i]<<endl;
            }
        }
        //--Choice: Exit
        else if(ch==8)
        {
            break;
        }
    }

}
