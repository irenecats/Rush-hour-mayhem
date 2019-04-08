#include "StateEnPausa.h"

#include <iostream>

StateEnPausa* StateEnPausa::instancia = nullptr;

StateEnPausa* StateEnPausa::instance()
{
    if(!instancia)
        instancia = new StateEnPausa;

    return instancia;
}

ID_State StateEnPausa::input(int teclaPulsada)
{
    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::Escape)
        next_state = ID_State::enJuego;

    return next_state;
}

void StateEnPausa::update()
{
    // update del estado pausa
}

void StateEnPausa::render(Window &window, const float updateTickTime)
{
    window.clear();
    // render del menu de pausa
    window.display();
}

StateEnPausa::StateEnPausa()
{
    id = ID_State::enPausa;
}

StateEnPausa::~StateEnPausa()
{
    //dtor
}
