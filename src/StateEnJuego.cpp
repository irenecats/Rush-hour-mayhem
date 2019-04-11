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
    {
        next_state = ID_State::enPausa;
    }
    else if(teclaPulsada == sf::Keyboard::G)
    {
        next_state = ID_State::enPuntuacion;
    }
    else if(teclaPulsada == sf::Keyboard::Space && ruta->getActiva() && ruta->getDiagActual()==1)
    {
        reloj.restart();
        ruta->pasarDialogo();
    }
    else if(teclaPulsada == sf::Keyboard::O){
        reloj.restart();
        ruta->haLlegado();
    }
    else if(teclaPulsada == sf::Keyboard::B && ruta->getActiva() && ruta->getDiagActual()==0)
    {
        reloj.restart();
        ruta->setDiagActual(2);
    }
    return next_state;
}

void StateEnJuego::update()
{
    //Cuando coche choque con ruta->getDestino,
    // delete ruta; rura = nullptr;
    // update del estado enJuego
    ruta->Update(reloj);
}

void StateEnJuego::render(Window &window, const float updateTickTime)
{
    window.clear();
    // render del menu de enJuego

    ruta->Render(window);
    window.display();
}

StateEnJuego::StateEnJuego()
{
    id = ID_State::enJuego;
    ruta = factoriaRuta.creaRuta(1);
    std::cout<<"Estado ruta: "<<ruta->getActiva()<<std::endl;
}

StateEnJuego::~StateEnJuego()
{
    //dtor
}
