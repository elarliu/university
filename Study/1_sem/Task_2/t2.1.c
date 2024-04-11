#include <stdio.h>

enum
{
    ERROR_CODE_FOR_INPUT_COEFF = 1,
    ERROR_CODE_FOR_INPUT_EPS = 2,
};

double
sqrt_(double x, double eps);

int
main(void)
{
    double eps,x,rt,s1,s2;
    
    s1 = scanf("%lf",&eps);
    
    

    while ((s2 = scanf(" %lf",&x))!=EOF && s2!=0)
    { 
        rt = sqrt_(x,eps);
        printf("Square root of %.10g: %.10g\n",x,rt);
    } 
    
    if (s1==0)
    {
        fprintf(stderr, "There is an error in EPS input: %d\n", ERROR_CODE_FOR_INPUT_EPS);
        return ERROR_CODE_FOR_INPUT_EPS;
    }
    else if (s2==0)
    {
        fprintf(stderr, "There is an error in X input: %d\n", ERROR_CODE_FOR_INPUT_COEFF);
        return ERROR_CODE_FOR_INPUT_COEFF;
    }

    return 0;
    
}

double
sqrt_(double x, double eps)
{
    double rt_1,rt_2,a;
    rt_1 = 1;
    do
    {
        rt_2 = (rt_1 + (x/rt_1))*(0.5);
        // printf("%lf %lf\n",rt_1,rt_2);
        a = rt_1 - rt_2;
        if (a<0)
        {
            a = -a;
        }
        rt_1 = rt_2;
    } while (a>=eps);
    
    return rt_2;
    
}