/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// TO STUDENTS: try to define/undefine this macro to see what happens
//#define ISSUE_WITH_INCOMPLETE_TYPE

/**
 * NOTE: the ISO C11 standard is more flexible because it is able to find later definitions of incomplete types.
 * For instance, with ISO C90 standard the following fragment doesn't compile:
 *   typedef struct customer_s customer_t;
 *   void do_task1(customer_t c); // KO: customer_t has an unknown size
 * because of the second line where the size of the incomplete type is unknown.
 * However, the same code fragment compiles smoothly in the ISO C11 standard.
 */


/* Declares an incomplete structure type and a derived pointer type */
struct customer_s;
typedef struct customer_s customer_t;
typedef customer_t* customer_ptr_t;

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
void do_task1(customer_t c); /* KO: customer_t has an unknown size */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

/* NOTE: in principle, a pointer to an incomplete type can be used as parameter, provided that if the function dereferences it then the complete definition of the type is fully available. Here below there are examples: the first one doesn't work while the second one does. */

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
void do_task2(customer_ptr_t pc); /* KO: a pointer to an incomplete type can be used as parameter, but since the function dereferences it and the definition of the function is before the one of the type, the compiler will generate an error */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

void do_task3(customer_ptr_t pc); /* OK: a pointer to an incomplete type can be used as parameter, provided that if the function dereferences it then the complete definition of the type is fully available */

void do_task4(customer_ptr_t pc); /* OK: same as above */

customer_ptr_t create_customer(const char* name, int age); /* OK: same as above */
void destroy_customer(customer_ptr_t pc); /* OK: same as above */

int main()
{
    const char *names[] = {"Customer 1", "Customer 2", "Customer 3", "Customer 4", "Customer 5"};
    int ages[] = {30, 35, 40, 45, 50};
    size_t i;

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
    customer_t customer; /* KO: customer_t is not complete */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
    customer_t customers[]; /* KO: customer_t is not complete */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

    customer_ptr_t pc; /* OK: pointer to an incomplete type */

    customer_ptr_t pcs[5]; /* OK: array of pointer to an incomplete type */

    pc = create_customer("John Doe", 39);
    for (i = 0; i < sizeof pcs/sizeof pcs[0]; ++i)
    {
        pcs[i] = create_customer(names[i], ages[i]);
    }

    do_task3(pc); /* OK */

    do_task4(pc); /* OK */

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
    *pc; /* KO: cannot dereference a pointer to an incomplete type */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

    (void) pcs[0]; /* OK: each array element is a pointer to an incomplete type. NOTE: the cast to void is only needed to avoid the 'statement with no effect' warning from the compiler. */

    do_task3(pcs[0]); /* OK */

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
    *(pcs[0]); /* KO: cannot dereference a pointer to an incomplete type */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

    for (i = 0; i < sizeof pcs/sizeof pcs[0]; ++i)
    {
        destroy_customer(pcs[i]);
    }
    destroy_customer(pc);

    return 0;
}

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
void do_task1(customer_t c) { } /* KO: customer_t has not been completed yet */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
void do_task2(customer_ptr_t pc) { pc->age; } /* KO: customer_t has not been completed yet */
#endif // ISSUE_WITH_INCOMPLETE_TYPE

#ifndef ISSUE_WITH_INCOMPLETE_TYPE
/* Completes the incomplete structure type declared above */
struct customer_s
{
    char *name;
    int age;
};
#endif // ISSUE_WITH_INCOMPLETE_TYPE

customer_ptr_t create_customer(const char* name, int age)
{
    customer_ptr_t pc = NULL;
    int ok = 0;

    pc = malloc(sizeof(customer_t));
    if (pc != NULL)
    {
        size_t name_len = strlen(name);
        pc->name = malloc(name_len+1);
        if (pc->name != NULL)
        {
            strcpy(pc->name, name);
            pc->age = age;
            ok = 1;
        }
    }

    if (!ok && pc != NULL)
    {
        free(pc);
        pc = NULL;
    }

    return pc;
}

void destroy_customer(customer_ptr_t customer)
{
    if (customer != NULL)
    {
        free(customer->name);
        free(customer);
    }
}

void do_task3(customer_ptr_t pc)
{
    (void) pc->age; /* NOTE: the cast to void is only needed to avoid the 'statement with no effect' warning from the compiler.*/
}

void do_something(customer_t c)
{
    (void) c.age; /* OK: the "main" cannot see this function, but other functions (like do_task4) can. NOTE: the cast to void is only needed to avoid the 'statement with no effect' warning from the compiler. */
}

void do_task4(customer_ptr_t pc) { do_something(*pc); }

#ifdef ISSUE_WITH_INCOMPLETE_TYPE
# error Try to define/undefine macro ISSUE_WITH_INCOMPLETE_TYPE to see issues involving incomplete types
#endif // ISSUE_WITH_INCOMPLETE_TYPE
