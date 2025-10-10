#include <stdio.h>

struct Student
{
    int rollNo;
    char name[20];
    int marks1;
    int marks2;
    int marks3;
    int total;
    float average;
};

// Calculating Average
float calculate_marks(int totalMarks)
{

    float avg = (float)totalMarks / 3.0;

    return avg;
}

// Assigning Grade
void assignGrade(int avg)
{
    if (avg >= 85)
    {
        printf("Grade: %c\n", 'A');
        printf("Performance: %s\n", "*****");
    }
    else if (avg >= 70)
    {
        printf("Grade: %c\n", 'B');
        printf("Performance: %s\n", "****");
    }
    else if (avg >= 50)
    {
        printf("Grade: %c\n", 'C');
        printf("Performance: %s\n", "***");
    }
    else if (avg >= 35)
    {
        printf("Grade: %c\n", 'D');
        printf("Performance: %s\n", "**");
    }
    else
    {
        printf("Grade: %c\n", 'F');
    }
}

// Print roll no using recursion
void printNum(struct Student s[], int index, int n)
{
    if(index == n)
    {
        return;
    }
    printf("%d ", s[index].rollNo);
    printNum(s, index + 1, n);
}

int main()
{
    char exp[100];
    int n;

    printf("Enter the number of students: \n");
    scanf("%d", &n);

    getchar();

    struct Student s[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter rollno, name and marks of 3 subjects: ");
        fgets(exp, sizeof(exp), stdin);

        int j = 0;
        while (exp[j] != '\0')
        {
            if (exp[j] == '\n')
            {
                exp[j] = '\0';
                break;
            }
            j++;
        }

        int scanned = sscanf(exp, "%d %s %d %d %d", &s[i].rollNo, &s[i].name, &s[i].marks1, &s[i].marks2, &s[i].marks3);

        if(scanned != 5)
        {
            printf("Invalid Input\n");
            return 1;
        }

        if(s[i].marks1 < 0 || s[i].marks1 > 100 || s[i].marks2 < 0 || s[i].marks2 > 100 || s[i].marks2 < 0 || s[i].marks2 > 100)
        {
            printf("Invalid Marks\n");
            return 1;
        }

        s[i].total = s[i].marks1 + s[i].marks2 + s[i].marks3;
        s[i].average = calculate_marks(s[i].total);
    }

    printf("Student Results: \n");

    for(int i=0; i<n; i++)
    {
        printf("Roll No: %d\n", s[i].rollNo);
        printf("Name: %s\n", s[i].name);
        printf("Total Marks: %d\n", s[i].total);
        printf("Average: %f\n", s[i].average);
        assignGrade(s[i].average);
        printf("\n");
    }

    printf("List of Roll No via Recursion: ");
    printNum(s, 0, n);
}