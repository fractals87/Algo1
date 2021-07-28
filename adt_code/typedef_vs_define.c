/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <stdlib.h>
#include <time.h>

/*
#define WONT_COMPILE
*/
#define UNUSED(x) (void)x


#define dint16_t short
#define dintptr_t int*
#define dfunc_t void (*)(int)
#ifdef WONT_COMPILE
# define dtimer_t time_t[2]
#endif /* WONT_COMPILE */

typedef int tint16_t;
typedef int* tintptr_t;
typedef void (*tfunc_t)(int);
typedef time_t ttimer_t[2];


#ifdef WONT_COMPILE
static void do_dcallfunc(dfunc_t func)
{
    func(0);
}
#endif /* WONT_COMPILE */

static void do_tcallfunc(tfunc_t func)
{
    func(0);
}

void myfunc(int i)
{
    UNUSED(i);
}

int main()
{
    dint16_t di1, di2;
    dintptr_t dptr1, dptr2;
#ifdef WONT_COMPILE
    dtimer_t dtimer1, dtimer2;
#endif /* WONT_COMPILE */

    tint16_t ti1, ti2;
    tintptr_t tptr1, tptr2;
    ttimer_t ttimer1, ttimer2;

#ifdef WONT_COMPILE
    di1 = di2 = 0;
    dptr1 = dptr2 = &di1;
    do_dcallfunc(myfunc);
#else /* WONT_COMPILE */
    /* Just suppress 'unused variable' warnings */
    UNUSED(di1);
    UNUSED(di2);
    UNUSED(dptr1);
    UNUSED(dptr2);
#endif /* WONT_COMPILE */

    ti1 = ti2 = 0;
    tptr1 = tptr2 = &ti1;
    do_tcallfunc(myfunc);

    /* Just suppress 'unused variable' warnings */
    UNUSED(tptr1);
    UNUSED(tptr2);
    UNUSED(ttimer1);
    UNUSED(ttimer2);

    return 0;
}
