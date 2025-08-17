#include "singletons.h"

using namespace world;
std::shared_ptr<rng> rngFactory::generator = nullptr;
std::shared_ptr<stopwatch> stopwatchFactory::chronometer = nullptr;

std::shared_ptr<rng> rngFactory::getRNG() {
    if (!generator) {
        generator = std::make_shared<rng>(rng());
    }
    return generator;
}

std::shared_ptr<stopwatch> stopwatchFactory::getStopwatch() {
    if (!chronometer) {
        chronometer = std::make_shared<stopwatch>(stopwatch());
    }
    return chronometer;
}
