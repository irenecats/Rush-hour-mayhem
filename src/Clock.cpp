#include "Clock.h"

Clock::Clock() {
    reloj.restart();
}

int Clock::getElapsedTime() {
    reloj.getElapsedTime().asMilliseconds();
}

int Clock::restart() {
    return reloj.restart().asMilliseconds();
}

Clock::~Clock() {}
