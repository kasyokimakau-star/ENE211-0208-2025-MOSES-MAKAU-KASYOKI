#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Declaration of variables
    float a;
    float b;
    printf("please enter a\n");
    scanf("%f",&a);
    printf("please enter b\n");
    scanf("%f",&b);
    float sum;
    sum=a+b;
    printf("the sum is %f",sum);
    float diff;
    diff=a-b;
    printf("the diff is\n %f",diff);
    float mult;
    mult=a*b;
    printf("the mult is\n %f",mult);
    float quotient;
    quotient=a/b;
    printf("the quotient is\n %f",quotient);
    return 0;


}
