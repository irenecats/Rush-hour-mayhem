#ifndef JUEGO_H
#define JUEGO_H

#include "Clock.h"
#include "Window.h"
#include "StateManager.h"

#include <iostream>

class Juego
{
    public:
        static Juego* Instance();
        void iniciarJuego();
        virtual ~Juego();

        /*
            (Mateo)
            StateManager contiene los estados
            asi que para que los estados se comuniquen
            con StateManager, es necesario que las
            ordenes pasen por la clase Juego.

            Si del estado inicio quiero pasar a jugar,
            como Juego es Singleton, le puedo decir desde
            un estado especifico al propio Juego, que le diga
            a StateManager que cambie de estado.
        */

        void state_iniciar();
        void state_jugar();
        void state_pausar();
        sf::Vector2u getSizeWindow();
        /*
            Fin Mateo
        */

    protected:
        Juego();
        Juego(const Juego&);
        Juego &operator= (const Juego &);

    private:
        static Juego* instancia;
        const float updateTickTime = 1000/15;
        Clock clock;
        Window window;
        //Esto es una idea que tendra que mirar Moni:
        //bool[] pressedKeys = {false, false, false, false, false}; // left, right, up, down, powerup

        void buclePrincipal();
        void checkInput();

        StateManager stateManager;
};

#endif // JUEGO_H
