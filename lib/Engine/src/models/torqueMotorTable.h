#ifndef TORQUEMOTORTABLE_H
#define TORQUEMOTORTABLE_H

// trying to consume as little memory as possible
// multiply rpm by 100
// torque is in percentage from 0 to 100
struct torqueMotorTable
{
    unsigned char rpm;
    unsigned char torque;
} rawMotorTable[] = {
    { 10,27 },
    { 11,42 },
    { 12,46 },
    { 13,50 },
    { 14,54 },
    { 15,57 },
    { 16,62 },
    { 17,57 },
    { 18,66 },
    { 19,74 },
    { 20,78 },
    { 21,79 },
    { 22,78 },
    { 23,83 },
    { 24,90 },
    { 25,94 },
    { 26,95 },
    { 27,96 },
    { 28,97 },
    { 29,98 },
    { 30,99 },
    { 31,99 },
    { 32,100 },
    { 33,100 },
    { 34,100 },
    { 35,100 },
    { 36,99 },
    { 37,99 },
    { 38,98 },
    { 39,97 },
    { 40,96 },
    { 41,95 },
    { 42,93 },
    { 43,92 },
    { 44,90 },
    { 45,89 },
    { 46,87 },
    { 47,86 },
    { 48,85 },
    { 49,84 },
    { 50,83 },
    { 51,80 },
    { 52,77 },
    { 53,75 },
    { 54,74 },
    { 55,73 },
    { 56,70 },
    { 57,68 },
    { 58,65 },
    { 59,64 },
    { 60,63 },
};

#endif //TORQUEMOTORTABLE_H