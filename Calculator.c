#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
            temp = temp * number[i + 1];
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
    for (int i = 0; i < *newOpCount; i++)
    {
        if (newOp[i] == '+')
        {
            result = result + newNum[i + 1];
        }
        else
        {
            result = result - newNum[i + 1];
        }
    }
    printf("Result is : %d", result);
}

int main()
{
    printf("Enter Expression: \n");
    char exp[100];
    fgets(exp, sizeof(exp), stdin);

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
