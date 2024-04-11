// задача 18

/*  Определите, каким образом при выполнении операции присваивания
 и явном приведении происходит преобразование беззнаковых целых 
 (M-битовое представление ) к беззнаковым целым ( N-битовое представление ) 
 при M > N, M = N, M < N. */

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
int 
main(void) 
{
    putchar('\n');
    unsigned int x1,x3,x4;
    unsigned long z1,z2,z3;

    //int -> long
    x1 = UINT16_MAX;
    z2 = x1;
    z3 = (long) (x1); 
    
    // long -> int
    z1 = ULLONG_MAX;

    x3 = z1;
    x4 = (int)(z1);


    printf("long = int %10lu lont = (long) short %10lu\n",z2,z3);
    printf("int = long %10u int = (int) long %10u\n",x3,x4);

    putchar('\n');

    return 0;
    
}

/* M<N в N помещается значение N */
/* M=N в N помещается значение N */
/* M>N в N помещается M%(2^N) */