#ifndef STATEENPUNTUACION_H
#define STATEENPUNTUACION_H

#include "State.h"

class StateEnPuntuacion : public State
{
    public:

        static StateEnPuntuacion* instance();

        ID_State input(int);
        void update();
        void render(Window&, const float);

        ~StateEnPuntuacion();

    private:

        static StateEnPuntuacion* instancia;

        StateEnPuntuacion();
};

#endif // STATEENPUNTUACION_H
