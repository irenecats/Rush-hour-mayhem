#include "Juego.h"

Juego* Juego::instancia = nullptr;

Juego::Juego()
{
    stateManager.iniciar();
}

Juego::~Juego()
{

}

Juego* Juego::Instance() {
    if (!instancia) {
        instancia = new Juego();
    }
    return instancia;
}

void Juego::buclePrincipal() {
    while (this->window.isOpen())
    {
        checkInput();

        if(clock.getElapsedTime() > updateTickTime)
        {
            stateManager.update(); //Pasar el tiempo por aqui?
            clock.restart();
        }

        float percentTick = std::min(1.0f, clock.getElapsedTime()/updateTickTime);
        //std::cout << clock.getElapsedTime()/updateTickTime << std::endl;
        stateManager.render(window, percentTick);

    }
}

void Juego::checkInput() {

    /*
        (Comentado por Mateo)

        ///////////////////////////////////////////////////////////////////////

        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        stateManager.pausar();

                    else if (event.key.code == sf::Keyboard::P)
                        std::cout << "Power-up" << std::endl;

                    else if (event.key.code == sf::Keyboard::Return) // esto es temporal, es solo para pasar al estado "enJuego"
                        stateManager.jugar();

                    break;
                default:
                    break;
            }///////////////////////////////////////////////////////////////////////
        }

        /////////////////////////////////////////////////////////////////////////

        Mi  propuesta es que los eventos se detecten en window.event(),
        y que si se pulsa una tecla, devuelva un entero. Este entero es la tecla
        pulsada, que se maneja en stateManager.input()
    */

    stateManager.input(window.event());
}

void Juego::iniciarJuego() {
    buclePrincipal();
}

void Juego::state_iniciar()
{
    stateManager.iniciar();
}

void Juego::state_jugar()
{
    stateManager.jugar();
}

void Juego::state_pausar()
{
    stateManager.pausar();
}

sf::Vector2u Juego::getSizeWindow()
{
    return window.getSize();
}
