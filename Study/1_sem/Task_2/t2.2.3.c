#include <stdio.h>

enum
{
    ERROR_CODE_FOR_INPUT_COEFF = 1,
    ERROR_CODE_FOR_INPUT_N = 2,
    ERROR_CODE_FOR_INPUT_X = 3,
};

int 
main(void)
{
    double x,intgrl,a,n;
    int s1,s2,s3;
    intgrl = 0;
    
    s1 = scanf("%lf",&n);
    
    s2 = scanf("%lf",&x);   
    // printf("%lf\n",n);

    while ((s3 = scanf("%lf",&a))!=EOF && s3!=0)
    {
        // printf("%lf %lf",a,n+)
        intgrl = intgrl*x + a*(1/(n+1));
        --n;

    }
    
    intgrl *= x;

    if (s1==0)
    {
        fprintf(stderr, "There is an error in N input: %d\n", ERROR_CODE_FOR_INPUT_N);
        return ERROR_CODE_FOR_INPUT_N;
    }
    else if (s2==0)
    {
        fprintf(stderr, "There is an error in X input: %d\n", ERROR_CODE_FOR_INPUT_X);
        return ERROR_CODE_FOR_INPUT_X;
    }
    else if (s3==0)
    {
        fprintf(stderr, "There is an error in coefficient input: %d\n", ERROR_CODE_FOR_INPUT_COEFF);
        return ERROR_CODE_FOR_INPUT_COEFF;
    }
    else
    {
        printf("Integral value: %.5lf\n",intgrl);
        
    }
    
    return 0;

}
