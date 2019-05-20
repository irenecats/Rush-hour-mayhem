#ifndef CLOCK_H
#define CLOCK_H
#include <SFML/Graphics.hpp>

class Clock
{
    public:
        Clock();
        virtual ~Clock();
        int getElapsedTime();
        int restart();
        int getElapsedTimeSeconds();

    protected:

    private:
        sf::Clock reloj;
};

#endif // CLOCK_H
