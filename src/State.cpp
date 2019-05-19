#include "State.h"

sf::Time State::tiempoPlayeado = sf::Time();

State::State()
{
    mTiempoLibre.openFromFile("resources/libre.wav");
    mMision.openFromFile("resources/mision.wav");
    mVictoria.openFromFile("resources/ffx.wav");
    mTienda.openFromFile("resources/tienda.wav");
    mFlechas.openFromFile("resources/blip.wav");
    mPobre.openFromFile("resources/mal.wav");
}

State::~State()
{
    //dtor
}

ID_State State::getID()
{
    return id;
}
