#ifndef STATEINICIO_H
#define STATEINICIO_H

#include "State.h"
#include "Jugador.h"

class StateInicio : public State
{
    public:

        static StateInicio* instance();

        ID_State input(int);
        void update();
        void render(Window&, const float);

        ~StateInicio();

    private:

        static StateInicio* instancia;

        StateInicio();
};

#endif // STATEINICIO_H
