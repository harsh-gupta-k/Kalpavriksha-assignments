#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generate_matrix(int (*matrix)[10], int num)
{
    srand(time(0));

    for(int row=0; row<num; row++)
    {
        for(int col=0; col<num; col++)
        {
            
            *(*(matrix + row) + col) = rand() % 256;
        }
    }
}

void printing_matrix(int (*matrix)[10], int num)
{
    for(int row=0; row<num; row++)
    {
        for(int col=0; col<num; col++)
        {
            printf("%d  ", *(*(matrix + row) + col));
        }
        printf("\n");
    }
}

void rotate_matrix(int (*matrix)[10], int num)
{
    for(int row=0; row<num; row++)
    {
        for(int col=row+1; col<num; col++)
        {
            int tempValue = *(*(matrix + row) + col);
            *(*(matrix + row) + col) = *(*(matrix + col) + row);
            *(*(matrix + col) + row) = tempValue;
        }
    }


    for(int row=0; row<num; row++)
    {
        for(int col=0; col<num; col++)
        {
            int start = 0;
            int end = num - 1;

            while(start <= end)
            {

                int tempValue = *(*(matrix + row) + start);
                *(*(matrix + row) + start) = *(*(matrix + row) + end);
                *(*(matrix + row) + end) = tempValue;
                start++;
                end--;
            }
        }
    }
}

void smoothing_filter(int (*matrix)[10], int num)
{
    int max_value = 256;

    for(int row=0; row<num; row++)
    {
        for(int col=0; col<num; col++)
        {
            int sum = 0;
            int count = 0;
            
            for(int k=row-1; k<=row+1; k++)
            {
                for(int l=col-1; l<=col+1; l++)
                {
                    if(k >= 0 && k < num && l >= 0 && l < num)
                    {
                        sum = sum + *(*(matrix + k) + l) % max_value;
                        count++;
                    }
                }
            }
            int newValue = sum / count;
            *(*(matrix + row) + col) = *(*(matrix + row) + col) + newValue * max_value;

        }
    }


    for(int row=0; row<num; row++)
    {
        for(int col=0; col<num; col++)
        {
            *(*(matrix + row) + col) = *(*(matrix + row) + col) / max_value;
        }
    }
}


int main()
{
    printf("Enter a number to generate a random matrix from 2 to 10: ");
    int num;
    scanf("%d", &num);

    if(num < 2 || num > 10)
    {
        printf("Invalid number");
        return 1;
    }
    
    int matrix[10][10];

    generate_matrix(matrix, num);  // Generate a random matrix

    printf("Original Matrix\n");
    printing_matrix(matrix, num); // Printing matrix

    printf("\n");

    rotate_matrix(matrix, num);  // Rotating Matrix

    printf("Rotated Matrix\n");
    printing_matrix(matrix, num);

    printf("\n");

    smoothing_filter(matrix, num);

    printf("Final Output after smoothing\n");
    printing_matrix(matrix, num);

}