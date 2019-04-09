#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.h"
#include "TexturaContainer.h"
#include "Interpolacion.h"

#define kVel 2
#define PI 3.141592
#define rad PI/180
#define kMaxSpeed 6
#define kRot 0.5
#define kFr 0.1

class Jugador
{
    public:
        Jugador();
        virtual ~Jugador();
        Jugador(const Jugador& other);

        static Jugador* instancia();

        void update(int time);
        void render(float ptick);

        Sprite getJugador();

        void setPowerUp(int pw);
        void activarPowerUp();

    private:
        static Jugador* claseJugador;

        float vel=0;

        int powerUp;
        bool powerUpActivado = false;

        Sprite jugador;
        Interpolacion lastState;
        Interpolacion newState;

};

#endif // JUGADOR_H
