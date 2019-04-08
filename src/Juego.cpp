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
        instancia = new Juego;
    }
    return instancia;
}

void Juego::buclePrincipal() {
    while (this->window.isOpen())
    {
        checkInput();

        if(clock.getElapsedTime() > updateTickTime)
        {
            stateManager.update();
            clock.restart();
        }

        stateManager.render(window, updateTickTime);
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
                    stateManager.pausar();

                else if (event.key.code == sf::Keyboard::P)
                    std::cout << "Power-up" << std::endl;

                else if (event.key.code == sf::Keyboard::Return) // esto es temporal, es solo para pasar al estado "enJuego"
                    stateManager.jugar();

                break;
            default:
                break;
        }
    }

    stateManager.input();
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
