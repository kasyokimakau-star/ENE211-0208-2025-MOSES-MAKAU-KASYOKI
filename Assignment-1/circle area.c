#include <stdio.h>
#include <stdlib.h>

int main()
{
    //declaration of variables
    const float pi=3.142;
    float radius;
    float area;

    printf("Please enter radius: ");
    scanf("%f",&radius);
    area=pi*radius*radius;
    printf("The area is\n %f",area);
    return 0;
}
