#include "StateEnJuego.h"

StateEnJuego* StateEnJuego::instancia = nullptr;

StateEnJuego* StateEnJuego::instance()
{
    if(!instancia)
        instancia = new StateEnJuego;

    return instancia;
}

ID_State StateEnJuego::input(int teclaPulsada)
{
    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::Escape)
        next_state = ID_State::enPausa;
    else if(teclaPulsada == sf::Keyboard::G)
        next_state = ID_State::enPuntuacion;

    return next_state;
}

void StateEnJuego::update()
{
    // update del estado enJuego
}

void StateEnJuego::render(Window &window, const float updateTickTime)
{
    window.clear();
    // render del menu de enJuego
    window.display();
}

StateEnJuego::StateEnJuego()
{
    id = ID_State::enJuego;
}

StateEnJuego::~StateEnJuego()
{
    //dtor
}
