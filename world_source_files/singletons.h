#ifndef AP_SINGLETONS_H
#define AP_SINGLETONS_H

#include "rng.h"
#include "stopwatch.h"
#include <memory>

namespace world {
    class rngFactory {
        static std::shared_ptr<rng> generator;

    public:
        /*
         * if the random number generator doesn't exist yet, it will produce it then it will return a shared pointer to
         * it
         *
         * return: a shared pointer to the random number generator
         */
        std::shared_ptr<rng> getRNG();

        ~rngFactory() = default;

        rngFactory() = default;
    };

    class stopwatchFactory {
    private:
        static std::shared_ptr<stopwatch> chronometer;

    public:
        /*
         * if the stopwatch doesn't exist yet, it will produce it then it will return a shared pointer to it
         *
         * return: a shared pointer to the stopwatch
         */
        std::shared_ptr<stopwatch> getStopwatch();

        ~stopwatchFactory() = default;

        stopwatchFactory() = default;
    };
} // namespace dj
#endif //AP_SINGLETONS_H
