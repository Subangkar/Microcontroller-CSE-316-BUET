#include<stdio.h>
#include<stdlib.h>

#define N 8
int symbol[N];
int matrix[N][N];
void rotateLeftMatrix()
{
	// Consider all squares one by one
	int r,c,temp;
	for (r = 0; r < N / 2; r++)
	{
		// Consider elements in group of 4 in
		// current square
		for (c = r; c < N-r-1; c++)
		{
			// store current cell in temp variable
			temp = matrix[r][c];
			
			// move values from right to top
			matrix[r][c] = matrix[c][N-1-r];
			
			// move values from bottom to right
			matrix[c][N-1-r] = matrix[N-1-r][N-1-c];
			
			// move values from left to bottom
			matrix[N-1-r][N-1-c] = matrix[N-1-c][r];
			
			// assign temp to left
			matrix[N-1-c][r] = temp;
		}
	}
}

// splits bits of symbol into a 2d array & stores in matrix
void makeMatrix()
{
	int r,c;
	for (r = 0; r < N; r++)
	{
		for (c = 0; c < N; c++)
		{
			matrix[r][c] = (symbol[r] & (1<<(N-1-c)))!=0;
		}
	}
}

// splits bits of symbol into a 2d array & stores in matrix
void makeSymbol()
{
	int r,c;
	for (r = 0; r < N; r++)
	{
		symbol[r]=0;
		for (c = 0; c < N; c++)
		{
			symbol[r] |= (matrix[r][c] << (N-1-c));
		}
	}
}
 
// Function to print the matrix
void displayMatrix(int matrix[N][N])
{
    int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            // printf("%2d ", matrix[i][j]);
            if(matrix[i][j]) printf(".");
            else printf(" ");
 
        printf("\n");
    }
    printf("\n");
}
 
 
void print1DArray(int arr[],int n){
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%5d ",arr[i]);
    }
    printf("\n"); 
}

/* Driver program to test above functions */
int main()
{
    int sym[N] = {0,0b01111111,0b11111111,0b11001100,0b11001100,0b11001100,0b11111111,0b01111111};
    
    int i;
    for(i = 0; i < N; i++)
    {
        symbol[i] = sym[i];
    }
    
    makeMatrix();
    displayMatrix(matrix);
    print1DArray(symbol,N);
    makeSymbol();
    print1DArray(symbol,N);
    makeMatrix();
    displayMatrix(matrix);

    // rotateLeftMatrix();
    makeSymbol();
    makeMatrix();
    displayMatrix(matrix);

    rotateLeftMatrix();
    // makeMatrix();
    displayMatrix(matrix);

    rotateLeftMatrix();
    // makeMatrix();
    displayMatrix(matrix);


    return 0;
}
