#include <stdio.h>

enum
{
    ERROR_CODE_FOR_INPUT_COEFF = 1,
    ERROR_CODE_FOR_INPUT_X = 2,
};

int 
main(void)
{
    double x,fnc,drv,a;
    int s1,s2;
    fnc = 0;
    drv = 0;
    s1 = scanf("%lf",&x);

    // printf("%lf\n",x);

    while ((s2 = scanf("%lf",&a))!=EOF && s2!=0)
    {
        // printf("%lf\n",a);
        drv = drv*x + fnc;
        fnc = fnc*x + a;

    }
    

    if (s1==0)
    {
        fprintf(stderr, "There is an error in X input: %d\n", ERROR_CODE_FOR_INPUT_X);
        return ERROR_CODE_FOR_INPUT_X;
    }
    else if (s2==0)
    {
        fprintf(stderr, "There is an error in coefficient input: %d\n", ERROR_CODE_FOR_INPUT_COEFF);
        return ERROR_CODE_FOR_INPUT_COEFF;
    }
    else
    {
        printf("Function value: %.5lf\n",fnc);
        printf("Derivative value: %.5lf\n",drv);
    }

    return 0;


}