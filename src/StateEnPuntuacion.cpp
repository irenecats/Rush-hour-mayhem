#include "StateEnPuntuacion.h"

StateEnPuntuacion* StateEnPuntuacion::instancia = nullptr;

StateEnPuntuacion* StateEnPuntuacion::instance()
{
    if(!instancia)
        instancia = new StateEnPuntuacion;

    return instancia;
}

ID_State StateEnPuntuacion::input(int teclaPulsada)
{
    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::T)
        next_state = ID_State::enTienda;

    return next_state;
}

void StateEnPuntuacion::update()
{
    // update del estado pausa
}

void StateEnPuntuacion::render(Window &window, const float updateTickTime)
{
    window.clear();
    // render del menu de pausa
    window.display();
}

StateEnPuntuacion::StateEnPuntuacion()
{
    id = ID_State::enPuntuacion;
}

StateEnPuntuacion::~StateEnPuntuacion()
{
    //dtor
}
