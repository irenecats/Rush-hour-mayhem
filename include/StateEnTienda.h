#ifndef STATEENTIENDA_H
#define STATEENTIENDA_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "State.h"
#include "Sprite.h"
#include "TexturaContainer.h"
#include "FactoryPowerUp.h"

#define kMargen 20
#define tamanyoX 800
#define tamanyoY 600

class StateEnTienda : public State
{
    public:

        static StateEnTienda* instance();

        ID_State input(int);
        void update();
        void render(Window&, const float);

        ~StateEnTienda();

    private:

        static StateEnTienda* instancia;

        FactoryPowerUp* fpu;
        PowerUp* powerUp;
        PowerUp* powerUp2;
        PowerUp* powerUp3;

        int seleccionado = 0;
        int dineroAhorrado = 200; //sacar esta info desde jugador

        sf::Font* fuente;
        sf::Text* titulo;
        Sprite* cajaDialogo; //esto cambiar mas adelante

        std::vector<sf::RectangleShape*> powerUps;
        sf::RectangleShape* r1;
        sf::RectangleShape* r2;
        sf::RectangleShape* r3;

        std::vector<sf::Text*> precios;
        sf::Text* precio1;
        sf::Text* precio2;
        sf::Text* precio3;

        sf::Text* dineroJugador;
        sf::Text* nom;
        sf::Text* descrip;

        //Son de ejemplo
        std::vector<std::string> nombres;
        std::vector<std::string> descripciones;

        void configurarPowerUps(sf::RectangleShape*& r, sf::Color color, float n1, float n2);
        void configurarPrecios(sf::Text*& precio, int num, int numPowerUp);
        void configurarInfo(sf::Text*& tex, float x, float y);

        StateEnTienda();
};

#endif // STATEENTIENDA_H
