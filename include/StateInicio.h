#ifndef STATEINICIO_H
#define STATEINICIO_H

#include "State.h"
#include "Jugador.h"

class StateInicio : public State
{
    public:

        static StateInicio* instance();

        ID_State input(int);
        void update(int tiempo);
        void render(Window&, const float);

        void inicializar();
        void limpiar();

        ~StateInicio();

    private:

        static StateInicio* instancia;

        StateInicio();

        sf::RectangleShape* contenedorMenu = nullptr;

        sf::Font* fuente = nullptr;

        sf::Text* nuevaPartida = nullptr;
        sf::Text* cargarPartida = nullptr;
        sf::Text* instrucciones = nullptr;
        Sprite logo;
        sf::Text textoinstrucciones;

        std::vector<sf::Text*>* opciones = nullptr;
        int seleccion = 0;
        bool eninstrucciones;
};

#endif // STATEINICIO_H
