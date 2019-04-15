#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.h"
#include "TexturaContainer.h"
#include "Interpolacion.h"
#include "Bala.h"
#include "Clock.h"
#include "Window.h"


class Bala
{
    public:
        Bala(float _x, float _y,float rot, float _dirx, float _diry, float vel);

        void update();
        void render(Window&, float ptick);

        bool getaborrar();
        Sprite getBala();


    private:
        Sprite bala;
        Interpolacion lastState;
        Interpolacion newState;

        float dirx, diry, vel;

        Clock clock;
        bool aborrar = false;

};

#endif // BALA_H
