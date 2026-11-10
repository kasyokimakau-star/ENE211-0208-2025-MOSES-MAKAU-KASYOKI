#include <stdio.h>

int main(void)
{
    int registrationNumber;
    char name[50];
    int marks;
    int choice = 1;
    char grade;
    const char *comment;
    const char *status;

    while (choice == 1) {
        printf("\n---STUDENT INFORMATION---\n");

        printf("Registration: ");
        if (scanf("%d", &registrationNumber) != 1) {
            printf("Invalid registration number.\n");
            break;
        }

        printf("Name: ");
        scanf(" %49[^\n]", name);   /* allows spaces, limits length */

        do {
            printf("Marks (0-100): ");
            if (scanf("%d", &marks) != 1) {
                printf("Invalid input.\n");
                return 1;
            }
            if (marks < 0 || marks > 100)
                printf("Marks must be between 0 and 100.\n");
        } while (marks < 0 || marks > 100);

        status = (marks < 40) ? "FAILED" : "PASSED";

        if (marks >= 70)      grade = 'A';
        else if (marks >= 60) grade = 'B';
        else if (marks >= 50) grade = 'C';
        else if (marks >= 40) grade = 'D';
        else                  grade = 'F';

        switch (grade) {
            case 'A': comment = "Excellent"; break;
            case 'B': comment = "Very Good"; break;
            case 'C': comment = "Good";      break;
            case 'D': comment = "Pass";      break;
            default:  comment = "Failed";    break;
        }

        printf("\n\n---STUDENT RESULTS---\n");
        printf("Registration Number: %d\n", registrationNumber);
        printf("Name: %s\n", name);
        printf("Marks: %d\n", marks);
        printf("Status: %s\n", status);
        printf("Grade: %c\n", grade);
        printf("Comment: %s\n", comment);

        printf("Do you want to enter another student? (1=Yes, 0=No): ");
        if (scanf("%d", &choice) != 1)
            break;
    }

    return 0;
}
