#ifndef STATEENPAUSA_H
#define STATEENPAUSA_H

#include "State.h"

class StateEnPausa : public State
{
    public:

        static StateEnPausa* instance();

        ID_State input(int);
        void update();
        void render(Window&, const float);

        ~StateEnPausa();

    private:

        static StateEnPausa* instancia;

        StateEnPausa();
};

#endif // STATEENPAUSA_H
