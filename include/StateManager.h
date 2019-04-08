#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

#include "StateInicio.h"

#include <iostream>

/*
    State contiene los unicos estados posibles.

    En el constructor, se inicializa el estado a "nulo".

    En principio, ningun estado deberia volver al inicio.

    Por cada estado adicional, habra una funcion que gestione
    la transicion entre cada estado.
*/

class StateManager
{
    public:

        StateManager();
        ~StateManager();

        void iniciar();
        void jugar();
        void pausar();

        void input(int);
        void update();
        void render(Window&, const float);

    private:

        static State* estadoActual;

};

#endif // STATEMANAGER_H
