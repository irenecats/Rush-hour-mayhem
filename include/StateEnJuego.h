#ifndef STATEENJUEGO_H
#define STATEENJUEGO_H

#include "State.h"

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

        StateEnJuego();
};

#endif // STATEENJUEGO_H
