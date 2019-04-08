#ifndef STATEINICIO_H
#define STATEINICIO_H

#include "State.h"

class StateInicio : public State
{
    public:

        static StateInicio* instance();

        void input();
        void update();
        void render(Window&, const float);

        ~StateInicio();

    private:

        static StateInicio* instancia;

        StateInicio();
};

#endif // STATEINICIO_H
