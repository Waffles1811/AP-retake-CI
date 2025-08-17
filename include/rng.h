#ifndef AP_RNG_H
#define AP_RNG_H

#include <cstdlib>

namespace world {
    class rng {
    public:
        /*
         *
         * return: a random number between min and max-1
         *
         */
        int generateRandomint(int min, int max);

        ~rng() = default;

        rng() = default;
    };
} // namespace dj


#endif //AP_RNG_H
