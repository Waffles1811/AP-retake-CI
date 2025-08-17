#include "stopwatch.h"

using namespace std::chrono;

float world::stopwatch::gameTimeTic() {
    auto curTime = std::chrono::steady_clock::now();
    duration<float> elapsedTime = duration_cast<duration<float>>(curTime - logicTime);
    logicTime = curTime;
    // std::cout << elapsedTime.count() << std::endl;
    // return 0.01; // for debugging
    return elapsedTime.count(); // for real stuff
}

float world::stopwatch::reprTimeTic() {
    auto curTime = std::chrono::steady_clock::now();
    duration<float> elapsedTime = duration_cast<duration<float>>(curTime - reprTime);
    reprTime = curTime;
    // std::cout << elapsedTime.count() << std::endl;
    // return 0.01; // for debugging
    return elapsedTime.count(); // for real stuff
}
