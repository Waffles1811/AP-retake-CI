#ifndef AP_STOPWATCH_H
#define AP_STOPWATCH_H

#include <chrono>

namespace world {
    class stopwatch {
    protected:
        std::chrono::steady_clock::time_point logicTime;
        std::chrono::steady_clock::time_point reprTime;

    public:
        /*
         *
         * measures time since last time this function was called
         *
         * return: time since last tic
         *
         */
        float gameTimeTic();
        float reprTimeTic();
        stopwatch() = default;

        ~stopwatch() = default;
    };
} // namespace dj
#endif // AP_STOPWATCH_H
