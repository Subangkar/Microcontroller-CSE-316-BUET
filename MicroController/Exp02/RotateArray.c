#include<stdio.h>
#include<stdlib.h>

void displayMatrix(int **matrix,int N);
 
// An Inplace function to rotate a N r N matrix
// by 90 degrees in anti-clockwise direction
int symbol[8];
int matrix[8][8];
void rotateLeftMatrix()
{
    int N=8;
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
 
// Function to print the matrix
void displayMatrix(int **matrix,int N)
{
    int i,j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%2d ", matrix[i][j]);
 
        printf("\n");
    }
    printf("\n");
}
 
 
/* Driver program to test above functions */
int main()
{
    int N=4;
 
    int i,j;   // Test Case 1
    int **matrix = (int**)malloc(4*sizeof(int*));

    for(i=0;i<4;i++)
    {
        matrix[i] = (int*)malloc(4*sizeof(int));
    }

    for(i=0;i<4;i++)
    {
        
        for(j = 0; j < 4; j++)
        {
            matrix[i][j] = i+j+1;
        }
        
    }

 
 
    // Tese Case 2
    /* int matrix[N][N] = {
                        {1, 2, 3},
                        {4, 5, 6},
                        {7, 8, 9}
                    };
     */
 
    // Tese Case 3
    /*int matrix[N][N] = {
                    {1, 2},
                    {4, 5}
                };*/
 
    //displayMatrix(matrix);
 
    displayMatrix(matrix,N);

    rotateLeftMatrix(matrix,N);
    displayMatrix(matrix,N);
    rotateLeftMatrix(matrix,N);
    displayMatrix(matrix,N);
    rotateLeftMatrix(matrix,N);
    displayMatrix(matrix,N);
    rotateLeftMatrix(matrix,N);
 
    // Print rotated matrix
    displayMatrix(matrix,N);

    for(i=0;i<4;i++)
    {
        free(matrix[i]);
    }
    free(matrix);
 
    return 0;
}
