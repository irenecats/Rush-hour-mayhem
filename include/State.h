#ifndef STATE_H
#define STATE_H

#include "Window.h"
#include "Camara.h"
#include "Jugador.h"

enum ID_State { inicio, enJuego, enPausa, enPuntuacion, enTienda };

class State
{
    public:

        State();
        ~State();

        ID_State getID();

        virtual ID_State input(int)   = 0;
        virtual void update()  = 0;
        virtual void render(Window&, const float)  = 0;

    protected :

        ID_State id;

};

#endif // STATE_H
