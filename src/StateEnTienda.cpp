#include "StateEnTienda.h"

StateEnTienda* StateEnTienda::instancia = nullptr;

StateEnTienda* StateEnTienda::instance()
{
    if(!instancia)
        instancia = new StateEnTienda;

    return instancia;
}

ID_State StateEnTienda::input(int teclaPulsada)
{
    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::Return)
        next_state = ID_State::enJuego;

    return next_state;
}

void StateEnTienda::update()
{
    // update de tienda
}

void StateEnTienda::render(Window& window, const float updateTickTime)
{
    window.clear();
    // render de tienda
    window.display();
}

StateEnTienda::StateEnTienda()
{
    id = ID_State::enTienda;
}

StateEnTienda::~StateEnTienda()
{
    //dtor
}
