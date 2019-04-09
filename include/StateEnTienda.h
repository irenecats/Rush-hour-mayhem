#ifndef STATEENTIENDA_H
#define STATEENTIENDA_H

#include "State.h"

class StateEnTienda : public State
{
    public:

        static StateEnTienda* instance();

        ID_State input(int);
        void update();
        void render(Window&, const float);

        ~StateEnTienda();

    private:

        static StateEnTienda* instancia;

        StateEnTienda();
};

#endif // STATEENTIENDA_H
