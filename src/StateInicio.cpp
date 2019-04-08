#include "StateInicio.h"

StateInicio* StateInicio::instancia = nullptr;

StateInicio* StateInicio::instance()
{
    if(!instancia)
        instancia = new StateInicio;

    return instancia;
}

void StateInicio::input()
{
    // input de la ventana
}

void StateInicio::update()
{
    // update del estado inicio
}

void StateInicio::render(Window &window, const float updateTickTime)
{
    // render del estado inicio
    window.clear();
    window.display();
}

StateInicio::StateInicio()
{
    id = ID_State::inicio;
}

StateInicio::~StateInicio()
{
    //dtor
}
