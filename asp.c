#include "asp.h"

const int MBIG = 0x7FFFFFFF;
const int MSEED = 161803398;
const int MZ = 0;

int inext;
int inextp;
int SeedArray[56];

void
Random(int Seed)
{
    int ii;
    int mj, mk;

    /* This algorithm comes from Numerical Recipes in C (2nd Ed.) */
    int subtraction = (Seed == (int)(0x80000000)) ? 0x7FFFFFFF : Seed;
    mj = MSEED - subtraction;
    SeedArray[55] = mj;
    mk = 1;
    for (int i = 1; i < 55; i++) {
        ii = (21 * i) % 55;
        SeedArray[ii] = mk;
        mk = mj - mk;
        if (mk < 0) mk += MBIG;
        mj = SeedArray[ii];
    }
    for (int k = 1; k < 5; k++) {
        for (int i = 1; i < 56; i++) {
            SeedArray[i] -= SeedArray[1 + (i + 30) % 55];
            if (SeedArray[i] < 0) SeedArray[i] += MBIG;
        }
    }
    inext = 0;
    inextp = 21;
    Seed = 1;
}

int
InternalSample()
{
    int retVal;
    int locINext = inext;
    int locINextp = inextp;

    if (++locINext >= 56) locINext = 1;
    if (++locINextp >= 56) locINextp = 1;

    retVal = SeedArray[locINext] - SeedArray[locINextp];

    if (retVal == MBIG) retVal--;
    if (retVal < 0) retVal += MBIG;

    SeedArray[locINext] = retVal;

    inext = locINext;
    inextp = locINextp;

    return retVal;
}

double
Sample()
{
    return (InternalSample() * (1.0 / MBIG));
}

double
GetSampleForLargeRange()
{
    int result = InternalSample();
    if ((InternalSample() % 2) == 0) {
        result = -result;
    }
    double d = result;
    d += (0x7FFFFFFF - 1);
    d /= 2 * (unsigned int)(0x7FFFFFFF) - 1;
    return d;
}

int
Next(int minValue, int maxValue)
{
    if (minValue > maxValue) {
        return -1;
    }

    long range = (long)maxValue - minValue;
    if (range <= (long)0x7FFFFFFF) {
        return ((int)(Sample() * range) + minValue);
    } else {
        return (int)((long)(GetSampleForLargeRange() * range) + minValue);
    }
}
