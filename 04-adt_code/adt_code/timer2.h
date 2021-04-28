/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#ifndef TIMER2_H
#define TIMER2_H

#include <time.h>

/** Implementation of the \c timer2_t type. */
struct timer2_s
{
    time_t start;
    time_t stop;
};
/** Definition of \c timer2_t type. */
typedef struct timer2_s timer2_t;

#endif /* TIMER2_H */
