#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.h"
#include "TexturaContainer.h"
#include "Interpolacion.h"
#include "Window.h"
#include "Bala.h"

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

        void update();
        void render(Window&, float ptick);

        Sprite getJugador();
        Sprite getBrujula();

        void setPowerUp(int pw);
        void activarPowerUp();

        bool disparando();
        Bala* getBala();

        void updateBrujula(float targetX, float targetY);
        void renderBrujula(Window&, float ptick);

        void setDinero(int money);
        int getDinero();
        int getDineroTotal();

    private:
        static Jugador* claseJugador;

        int dinero;
        int dineroTotal;

        float vel=0;

        int powerUp;
        bool powerUpActivado = false;

        Sprite jugador;
        Interpolacion lastState;
        Interpolacion newState;

        Sprite brujula;

        Bala* bala = nullptr;

};

#endif // JUGADOR_H
