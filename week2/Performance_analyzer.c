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

    float average = (float)totalMarks / 3.0;

    return average;
}

// Assigning Grade
void assignGrade(int average)
{
    if (average >= 85)
    {
        printf("Grade: %c\n", 'A');
        printf("Performance: %s\n", "*****");
    }
    else if (average >= 70)
    {
        printf("Grade: %c\n", 'B');
        printf("Performance: %s\n", "****");
    }
    else if (average >= 50)
    {
        printf("Grade: %c\n", 'C');
        printf("Performance: %s\n", "***");
    }
    else if (average >= 35)
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
void printNum(struct Student s[], int index, int totalStudents)
{
    if(index == totalStudents)
    {
        return;
    }
    printf("%d ", s[index].rollNo);
    printNum(s, index + 1, totalStudents);
}

int main()
{
    char expression[100];
    int numOfStudents;

    printf("Enter the number of students: \n");
    scanf("%d", &numOfStudents);

    getchar();

    struct Student s[numOfStudents];

    for (int studentIndex  = 0; studentIndex < numOfStudents; studentIndex++)
    {
        printf("Enter rollno, name and marks of 3 subjects: ");
        fgets(expression, sizeof(expression), stdin);

        int charIndex = 0;
        while (expression[charIndex] != '\0')
        {
            if (expression[charIndex] == '\n')
            {
                expression[charIndex] = '\0';
                break;
            }
            charIndex++;
        }

        int scanned = sscanf(expression, "%d %s %d %d %d", &s[studentIndex].rollNo, &s[studentIndex].name, &s[studentIndex].marks1, &s[studentIndex].marks2, &s[studentIndex].marks3);

        if(scanned != 5)
        {
            printf("Invalid Input\n");
            return 1;
        }

        if(s[studentIndex].marks1 < 0 || s[studentIndex].marks1 > 100 || s[studentIndex].marks2 < 0 || s[studentIndex].marks2 > 100 || s[studentIndex].marks2 < 0 || s[studentIndex].marks2 > 100)
        {
            printf("Invalid Marks\n");
            return 1;
        }

        s[studentIndex].total = s[studentIndex].marks1 + s[studentIndex].marks2 + s[studentIndex].marks3;
        s[studentIndex].average = calculate_marks(s[studentIndex].total);
    }

    printf("Student Results: \n");

    for(int studentIndex=0; studentIndex<numOfStudents; studentIndex++)
    {
        printf("Roll No: %d\n", s[studentIndex].rollNo);
        printf("Name: %s\n", s[studentIndex].name);
        printf("Total Marks: %d\n", s[studentIndex].total);
        printf("Average: %f\n", s[studentIndex].average);
        assignGrade(s[studentIndex].average);
        printf("\n");
    }

    printf("List of Roll No via Recursion: ");
    printNum(s, 0, numOfStudents);
}