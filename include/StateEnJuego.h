#ifndef STATEENJUEGO_H
#define STATEENJUEGO_H

#include "State.h"
#include "Collision.h"
#include <Sprite.h>
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

        void inicializar();
        void limpiar();

        ~StateEnJuego();

    private:

        static StateEnJuego* instancia;
        FactoryRuta          factoriaRuta;
        Ruta*                ruta;
        sf::RectangleShape*  origen;
        sf::RectangleShape*  destino;
        Clock                reloj;
        bool                 colision;
        sf::Font             fuente;
        sf::Text             finRuta;
        StateEnJuego();
        void detectColisionRuta();
        void detectColisionMapa();
};

#endif // STATEENJUEGO_H
