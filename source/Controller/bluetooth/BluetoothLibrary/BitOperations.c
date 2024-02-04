#include <bluetooth/BluetoothLibrary/BitOperations.h>
#include <stdio.h>

uint8_t SetNbitToOne(uint8_t value, int n)
{
    return (value | (1 << n));
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
