#ifndef STATE_H
#define STATE_H

#include "Window.h"
#include "Camara.h"
#include "Jugador.h"
#include <SFML/Audio.hpp>

enum ID_State { inicio, enJuego, enPausa, enPuntuacion, enTienda };

class State
{
    public:

        State();
        ~State();

        ID_State getID();

        virtual ID_State input(int)   = 0;
        virtual void update(int tiempo)  = 0;
        virtual void render(Window&, const float)  = 0;

        virtual void inicializar() = 0;
        virtual void limpiar() = 0;

    protected :

        ID_State id;
        ID_State next_state;

        sf::Music mTiempoLibre;
        sf::Music mMision;
        sf::Music mVictoria;
        sf::Music mTienda;
        sf::Music mFlechas;
        sf::Music mPobre;

        static sf::Time tiempoPlayeado;
};

#endif // STATE_H
