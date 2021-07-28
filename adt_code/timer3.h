/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#ifndef MY_TIMER3_H
#define MY_TIMER3_H

/** Definition of \c timer3_t type */
typedef struct timer3_s* timer3_t; /* Pointer to an incomplete structure type). */


/**
 * Creates a new timer.
 *
 * \return The new timer.
 */
timer3_t timer3_create();

/**
 * Destroy a given timer.
 *
 * \param The timer to destroy
 */
void timer3_destroy(timer3_t timer);

/**
 * Starts or restarts the given timer.
 *
 * \param timer A timer.
 */
void timer3_start(timer3_t timer); 

/**
 * Stops the given timer.
 *
 * \param timer A timer.
 */
void timer3_stop(timer3_t timer); 

/**
 * Tells if the given timer is started.
 *
 * \param timer A timer.
 * \return \c 1 if the input timer is started; \c 0, otherwise.
 */
int timer3_is_started(timer3_t timer); 

/**
 * Tells if the given timer is stopped.
 *
 * \param timer A timer.
 * \return \c 1 if the input timer is stopped; \c 0, otherwise.
 */
int timer3_is_stopped(const timer3_t timer); 

/**
 * Returns the number of seconds elapsed since when the timer has been started
 * until the stopping time (or so far, if not stopped yet).
 *
 * \param p_timer A pointer to a timer.
 * \return the number of seconds elapsed, on success; \c a negative number, on
 *  error.
 */
double timer3_elapsed(const timer3_t timer); 

/* TO STUDENTS:
 *
 * You can add other useful functions like:
 *   time_t timer3_get_start_time(const timer3_t timer);
 *   time_t timer3_get_stop_time(const timer3_t timer);
 *   void timer3_reset(timer3_t timer);
 *   ...
 */

#endif /* MY_TIMER3_H */
