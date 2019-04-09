#include "StateInicio.h"

StateInicio* StateInicio::instancia = nullptr;

StateInicio* StateInicio::instance()
{
    if(!instancia)
        instancia = new StateInicio;

    return instancia;
}

ID_State StateInicio::input(int teclaPulsada)
{
    /*
        teclaPulsada es el input de la ventana
        en principio, en el estado de inicio,
        este sera el unico tipo de input.

        Se podria implementar el raton, pasando
        por parametro una struct que habria que
        definir, desde Juego->StateManager->
        ->State->StateInicio, lo necesario para
        controlar el funcionamiento del raton
        (posicion del cursor, click, etc).
    */

    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::Return)
        next_state = ID_State::enJuego;

    return next_state;
}

void StateInicio::update()
{
    // update del estado inicio
    //Jugador::instancia()->update(1);
}

void StateInicio::render(Window &window, const float updateTickTime)
{

Jugador::instancia();
    window.clear();
    //window.draw(Jugador::instancia()->jugador.getSprite());
    // render del menu de inicio
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
