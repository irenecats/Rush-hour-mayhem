#ifndef STATE_H
#define STATE_H

#include "Window.h"

typedef enum ID_State { inicio, enJuego, enPausa };

class State
{
    public:

        State();
        ~State();

        ID_State getID();

        virtual void input()   = 0;
        virtual void update()  = 0;
        virtual void render(Window&, const float)  = 0;

    protected :

        ID_State id;

};

#endif // STATE_H
