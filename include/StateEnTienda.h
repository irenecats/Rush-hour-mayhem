#ifndef STATEENTIENDA_H
#define STATEENTIENDA_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "State.h"
#include "Sprite.h"
#include "TexturaContainer.h"
#include "FactoryPowerUp.h"
#include "StateEnJuego.h"

#define kMargen 20
#define tamanyoX 800
#define tamanyoY 600

class StateEnTienda : public State
{
    public:

        static StateEnTienda* instance();

        ID_State input(int);
        void update(int tiempo);
        void render(Window&, const float);

        void inicializar();
        void limpiar();

        ~StateEnTienda();

    private:

        static StateEnTienda* instancia;
        StateEnTienda();

        FactoryPowerUp* fpu = nullptr;

        int seleccionado = 0;
        int dineroAhorrado = 200; //sacar esta info desde jugador

        sf::Font* fuente = nullptr;
        sf::Text* titulo = nullptr;
        sf::Text* dineroJugador = nullptr;
        sf::Text* ayudaPlayer = nullptr;

        std::vector<PowerUp*> powerUps;
        sf::RectangleShape* recSeleccion = nullptr;

        std::vector<sf::Text*> precios;
        sf::Text* precio1 = nullptr;
        sf::Text* precio2 = nullptr;
        sf::Text* precio3 = nullptr;

        std::vector<std::string> nombres;
        std::vector<std::string> descripciones;

        sf::Text* nom = nullptr;
        sf::Text* descrip = nullptr;
        Sprite* cajaDialogo = nullptr;

        void configurarPowerUps(PowerUp*& pu, float n1, float n2);
        void configurarPrecios(sf::Text*& precio, int num, int numPowerUp);
        void configurarInfo(sf::Text*& tex, int tamanyo, float x, float y);
        int numRandom(std::string tipoPowerUp);

        bool reiniciarTienda = false;
};

#endif // STATEENTIENDA_H
