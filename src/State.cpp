#include "State.h"

sf::Time State::tiempoPlayeado = sf::Time();

State::State()
{
    mIntro.openFromFile("resources/intro.wav");
    mTiempoLibre.openFromFile("resources/libre.wav");
    mMision.openFromFile("resources/mision.wav");
    mVictoria.openFromFile("resources/ffx.wav");
    mTienda.openFromFile("resources/tienda.wav");
    mFlechas.openFromFile("resources/blip.wav");
    mPobre.openFromFile("resources/mal.wav");
    mRadio.openFromFile("resources/love4eva.wav");
}

State::~State()
{
    //dtor
}

ID_State State::getID()
{
    return id;
}
