// 12 задача

/* Определите, каким образом "малое" целое расширяется до int 
(старшие разряды int заполняются нулями или знаковым разрядом "малого" целого ).*/

void 
print_binary( int num, int num_bits);

#include <stdio.h>

int 
main(void) 
{

    short a,b;
    int c,d;

    a = 1;
    b = -1;

    c = (int) a;
    d = (int) b;

    printf("%5d %5d\n",c,d);

    print_binary(c, sizeof(c)*8);
    print_binary(d, sizeof(d)*8);

    return 0;
    
}

/* старшие разряды заполняются знаковым разрядом */

void 
print_binary(int num, int num_bits) {
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    putchar('\n');
}