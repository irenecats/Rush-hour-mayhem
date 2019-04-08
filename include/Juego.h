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
