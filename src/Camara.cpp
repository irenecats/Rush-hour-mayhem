#include "Camara.h"

Camara* Camara::claseCamara = nullptr;

Camara* Camara::instancia() {
    if(claseCamara == nullptr)
        claseCamara = new Camara();

    return claseCamara;
}

Camara::Camara()
{
    fullview.setCenter(tamanyoX/2, tamanyoY/2);
    fullview.setSize(tamanyoX, tamanyoY);
    fullview.setViewport(sf::FloatRect(0, 0, 1, 1));

    carview.setCenter(Jugador::instancia()->getJugador().getPosition()[0], Jugador::instancia()->getJugador().getPosition()[1]);
    carview.setSize(tamanyoX, tamanyoY);
    carview.setViewport(sf::FloatRect(0, 0, 1, 1));
    carview.zoom(0.8);

}

Camara::~Camara()
{
    //dtor
}

sf::View Camara::getFullView(){
    return fullview;
}

sf::View Camara::getCarView(){
    return carview;
}

void Camara::centrarVista(){
    carview.setCenter(Jugador::instancia()->getJugador().getPosition()[0], Jugador::instancia()->getJugador().getPosition()[1]);
}
