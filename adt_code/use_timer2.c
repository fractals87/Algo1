/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <math.h>
#include "timer2.h"
#include <stdio.h>
#include <stdlib.h>

static void do_something(long n)
{
    while (n > 0)
    {
        exp(sqrt(n));
        --n;
    }
}

int main(int argc, char* argv[])
{
    long n = 200000000L;
    timer2_t timer;

    if (argc > 1)
    {
        n = atol(argv[1]);
    }

    time(&timer.start);

    do_something(n);

    time(&timer.stop);

    printf("Elapsed: %f seconds.\n", difftime(timer.stop, timer.start));

    return 0;
}
