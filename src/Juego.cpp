#include "Juego.h"
#include "Clock.h"
#include <iostream>

Juego* Juego::instancia = 0;

Juego::Juego()
{

}

Juego::~Juego()
{
    //dtor
}

Juego* Juego::Instance() {
    if (instancia == 0) {
        instancia = new Juego;
    }
    return instancia;
}

void Juego::buclePrincipal() {
    while (this->window.isOpen()) {
        checkInput();
        if (clock.getElapsedTime() > updateTickTime) {
            clock.restart();
            //estado.Update();
        }
        //estado.Render(updateTickTime);
        window.clear();
        window.display(); // Quitar estas dos líneas cuando tengamos el render
    }
}

void Juego::checkInput() {
    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    std::cout << "Escape (habrá que cambiar el estado a pausa)" << std::endl;
                else if (event.key.code == sf::Keyboard::P)
                    std::cout << "Power-up" << std::endl;
                break;
            default:
                break;
        }
    }
}

void Juego::iniciarJuego() {
    buclePrincipal();
}

/*
    public:
        void iniciarJuego();
    private:
        Clock clock;
        void buclePrincipal();
        void checkInput();*/
