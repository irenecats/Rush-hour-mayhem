#ifndef CAMARA_H
#define CAMARA_H
#include <SFML/Graphics.hpp>
#include "Jugador.h"

#define tamanyoX 800
#define tamanyoY 600

class Camara
{
    public:
        Camara();
        virtual ~Camara();
        static Camara* instancia();

        sf::View getFullView();
        sf::View getCarView();

        void centrarVista();

    protected:
    private:
        static Camara* claseCamara;

        sf::View fullview;
        sf::View carview;
};

//crear metodo para hacer zoom

#endif // CAMARA_H
