/*
 * timer.h
 *
 *  Created on: Feb 6, 2019
 *      Author: David "Dawn" Estes McKnight and Benjamin Korty
 */

#ifndef TIMER_H_
#define TIMER_H_

/**
 * Delays the program by the provided number of decrementation and comparison operations.
 * @param count The number of decrementation and comparison operations to perform.
 */
void wait_ticks(int count)
{
    volatile int ticks = count;
    while (ticks>0)
        ticks--;
}

/**
 * Converts the desired number of seconds to comparison+decrementation ticks for wait_ticks
 * @param seconds the desired number of seconds for wait_ticks to wait
 * @return the number of seconds for wait_ticks to wait
 */
int seconds_to_ticks(double seconds)
{
    double ticks_unrounded = (seconds * 1000000 - 9.896)/3.464;

    //round the ticks and return
    return (int)(ticks_unrounded + 0.5);
}

#endif
