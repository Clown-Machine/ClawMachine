#ifndef BIT
#define BIT

#include <stdio.h>
#include <stdint.h>

// in value sets nth bit to one (in a byte, from bit 0 to bit seven)
// Parameters: value and n position of the bit to be set
uint8_t SetNbitToOne(uint8_t value, int n);

// adds velocity as the last four bits in value
// Parameters: velocity and value in which to encode it
uint8_t encodeVelocity(uint8_t velocity, uint8_t value);

// adds velocity as the last six bits in value
// Parameters: target and value in which to encode it
uint8_t encodeTarget(uint8_t target, uint8_t value);

#endif
