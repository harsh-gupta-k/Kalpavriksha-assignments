#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<limits.h>

// removing spaces
void removeSpaces(char arr[])
{
    int j = 0;
    for (int i = 0; i < strlen(arr); i++)
    {
        if (arr[i] != ' ')
        {
            arr[j] = arr[i];
            j++;
        }
    }
    arr[j] = '\0';
}

// storing values in different array according to numbers and operators
void storingValues(int numbers[], char operators[], char exp[], int *numCount, int *opCount)
{
    int i = 0;
    while (exp[i] != '\0')
    {
        if (isdigit(exp[i]))
        {
            int num = 0;
            while (isdigit(exp[i]))
            {
                num = num * 10 + (exp[i] - '0');
                i++;
            }
            numbers[*numCount] = num;
            (*numCount)++;
        }
        else
        {
            operators[*opCount] = exp[i];
            (*opCount)++;
            i++;
        }
    }
}

// handling * or / operators
int handle_Operators(int newNumber[], char newOperator[], int number[], char operator[], int *newNumCount, int *newOpCount, int *opCount)
{
    int temp = number[0];
    for (int i = 0; i < *opCount; i++)
    {
        if (operator[i] == '*')
        {
            long long tempResult = (long long)temp * (long long)number[i+1];
            if(tempResult > INT_MAX || tempResult < INT_MIN)
            {
                printf("Error: Interger Overflow\n");
                return 0;
            }
            temp = (int)tempResult;
        }
        else if (operator[i] == '/')
        {
            if (number[i + 1] == 0)
            {
                printf("Error: Division by Zero");
                return 0;
            }


            temp = temp / number[i + 1];
        }
        else
        {
            newNumber[*newNumCount] = temp;
            (*newNumCount)++;
            newOperator[*newOpCount] = operator[i];
            (*newOpCount)++;
            temp = number[i + 1];
        }
    }
    newNumber[*newNumCount] = temp;
    (*newNumCount)++;
    return 1;
}

// handling + and - operators
void handleOperators(int newNum[], char newOp[], int *newOpCount)
{
    int result = newNum[0];
    long long tempResult;
    for (int i = 0; i < *newOpCount; i++)
    {
        if (newOp[i] == '+')
        {
            tempResult = (long long)result + (long long)newNum[i+1];
            if (tempResult > INT_MAX || tempResult < INT_MIN)
            {
                printf("Error: Integer Overflow\n");
                return;
            }
        }
        else
        {
            tempResult = (long long)result - (long long)newNum[i+1];
            if (tempResult > INT_MAX || tempResult < INT_MIN)
            {
                printf("Error: Integer Overflow \n");
                return;
            }
        }
        result = (int)tempResult;
    }
    printf("Result is : %d", result);
}

int main()
{
    printf("Enter Expression: \n");
    char exp[100];
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = '\0';


    removeSpaces(exp);

    for (int i = 0; i < strlen(exp); i++)
    {
        if (exp[i] >= 'a' && exp[i] <= 'z')
        {
            printf("Error: Invalid expression");
            return 0;
        }
    }

    int number[20] = {0};
    char operator[20] = {0};
    int numCount = 0;
    int opCount = 0;

    storingValues(number, operator, exp, &numCount, &opCount);

    if(opCount >= numCount)
    {
        printf("Error: Invalid Operands\n");
        return 1;
    }

    int newNum[100];
    int newNumCount = 0;
    char newOp[100];
    int newOpCount = 0;

    if (handle_Operators(newNum, newOp, number, operator, &newNumCount, &newOpCount, &opCount) == 0)
    {
        return 0;
    }

    handleOperators(newNum, newOp, &newOpCount);  
}