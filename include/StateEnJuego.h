#ifndef STATEENJUEGO_H
#define STATEENJUEGO_H

#include "State.h"
#include <iostream>
#include <FactoryRuta.h>
#include <Ruta.h>
#include <Clock.h>

class StateEnJuego : public State
{
    public:

        static StateEnJuego* instance();

        ID_State input(int);
        void update();
        void render(Window&, const float);

        ~StateEnJuego();

    private:

        static StateEnJuego* instancia;
        FactoryRuta          factoriaRuta;
        Ruta*                ruta;
        Clock                reloj;
        StateEnJuego();
};

#endif // STATEENJUEGO_H
