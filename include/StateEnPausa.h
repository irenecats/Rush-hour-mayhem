#ifndef STATEENPAUSA_H
#define STATEENPAUSA_H

#include "State.h"
#include "StateEnJuego.h"

class StateEnPausa : public State
{
    public:

        static StateEnPausa* instance();

        ID_State input(int);
        void update(int tiempo);
        void render(Window&, const float);

        void inicializar();
        void limpiar();

        ~StateEnPausa();

    private:

        static StateEnPausa* instancia;

        StateEnPausa();

        sf::RectangleShape* contenedorMenu = nullptr;

        sf::Font* fuente = nullptr;

        sf::Text* seguirPartida = nullptr;
        sf::Text* guardarPartida = nullptr;
        sf::Text* salir = nullptr;

        std::vector<sf::Text*>* opciones = nullptr;
        int seleccion = 0;
};

#endif // STATEENPAUSA_H
