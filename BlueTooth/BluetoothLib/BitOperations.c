#include "BitOperations.h"
#include <stdio.h>

#define MIN1 0
#define MAX1 100 ///////////////////////// ANGELA
#define MIN2 0
#define MAX2 15

uint8_t SetNbitToOne(uint8_t value, int n)
{
    return (value | (1 << n));
}

uint8_t mapTo15(uint8_t value)
{
    return (uint8_t)((MAX2 - MIN2) * (((float)value - (float)MIN1) / ((float)MAX1 - (float)MIN1)));
}

uint8_t encodeVelocity(uint8_t velocity, uint8_t value)
{
    velocity = velocity << 4;

    return (value | velocity);
}

uint8_t encodeTarget(uint8_t target, uint8_t value)
{
    target = target << 2;
    return (value | target);
}
