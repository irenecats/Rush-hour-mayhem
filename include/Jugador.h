#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.h"
#include "TexturaContainer.h"
#include "Interpolacion.h"
#include "Window.h"
#include "Bala.h"

#define kVel 10
#define PI 3.141592
#define rad PI/180
#define kMaxSpeed 34
#define kRot 0.25
#define kFr 1

class Jugador
{
    public:
        Jugador();
        virtual ~Jugador();
        Jugador(const Jugador& other);

        static Jugador* instancia();

        void update(int tiempo);
        void interpolar(float ptick);
        void dibujar(Window&);

        Sprite getJugador();
        Sprite getBrujula();
        int getPW() { return powerUp; }

        void setPowerUp(int pw);
        void activarPowerUp();
        bool esFantasma();
        bool muestroGuia();

        bool disparando();
        Bala* getBala();
        void borraBala();

        void updateBrujula(float targetX, float targetY);
        void renderBrujula(Window&, float ptick);

        void setDinero(int money);
        int getDinero();
        int getDineroTotal();

        void frenar(float colx, float coly);
        void nofrenar();
        void frenacoche();

        int getColisiones();
        void borrarColisiones();

        Clock turbo;

        bool getPowerUpActivado();
        bool getZoom();
        float getVel();
        int getNumColisiones();
        void setNumColisiones(int numero);

    private:
        static Jugador* claseJugador;

        int dinero = 0;
        int dineroTotal = 0;
        int numColisiones = 0;

        float vel = 0;

        float _dirx, _diry;

        int colisiones = 0;

        int powerUp;
        bool powerUpActivado = false;
        bool zoom = false;

        bool chocando = false;

        Sprite jugador;
        Interpolacion lastState;
        Interpolacion newState;

        Sprite brujula;
        Interpolacion lastStateB;
        Interpolacion newStateB;

        Bala* bala = nullptr;

};

#endif // JUGADOR_H
