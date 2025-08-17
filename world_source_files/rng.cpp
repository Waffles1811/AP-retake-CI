#include "rng.h"

int world::rng::generateRandomint(int min, int max) {
    if (min == max) {
        return min; // otherwise it will try to divide by 0 later
    }
    int retVal = rand();
    retVal = retVal % (max - min);
    retVal += min;
    return retVal;
}
