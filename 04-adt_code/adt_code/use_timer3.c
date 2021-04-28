/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <math.h>
#include "timer3.h"
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
    timer3_t timer;

    if (argc > 1)
    {
        n = atol(argv[1]);
    }

    timer = timer3_create();

    timer3_start(timer);

    do_something(n);

    timer3_stop(timer);

    printf("Elapsed: %f seconds.\n", timer3_elapsed(timer));

    /* Won't compile since information hiding is enforced
    printf("Started at: %s", ctime(&timer->start));
    printf("Stopped at: %s", ctime(&timer->stop));
    */

    timer3_destroy(timer);

    return 0;
}
