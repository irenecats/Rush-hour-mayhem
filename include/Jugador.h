#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.h"
#include "TexturaContainer.h"

#define kVel 2
#define PI 3.141592
#define rad PI/180
#define kMaxSpeed 4
#define kRot 0.5
#define kFr 0.01

class Jugador
{
    public:
        Jugador();
        virtual ~Jugador();
        Jugador(const Jugador& other);
        static Jugador* instancia();
        void update(int time);
        void render(float ptick);
        Sprite jugador;
    protected:
    private:
        static Jugador* claseJugador;
        float vel=0;
        int powerUp;

};

#endif // JUGADOR_H
