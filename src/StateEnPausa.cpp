#include "StateEnPausa.h"

#include <iostream>

StateEnPausa* StateEnPausa::instancia = nullptr;

StateEnPausa* StateEnPausa::instance()
{
    if(!instancia)
        instancia = new StateEnPausa;

    return instancia;
}

ID_State StateEnPausa::input(int teclaPulsada)
{
    next_state = id;

    if(teclaPulsada == sf::Keyboard::Up)
    {
        if(seleccion == 0)
            seleccion = (int) opciones->size() - 1;
        else
            seleccion--;
    }

    if(teclaPulsada == sf::Keyboard::Down)
    {
        if(seleccion >= (int) opciones->size() - 1)
            seleccion = 0;
        else
            seleccion++;
    }

    switch(teclaPulsada)
    {
        case sf::Keyboard::Return :
            if(seleccion == 0)
                next_state = ID_State::enJuego;
            break;

        case sf::Keyboard::Escape :
            limpiar(); // reinicia los valores (en este caso la seleccion se pone a 0 otra vez)
            next_state = ID_State::enJuego;
            break;

        default : break;
    }

    return next_state;
}

void StateEnPausa::update(int tiempo)
{
    for(int i = 0; i < (int) opciones->size(); ++i)
        if(seleccion == i)
            opciones->at(i)->setColor(sf::Color::White);
        else
            opciones->at(i)->setColor(sf::Color(128, 128, 128, 255));
}

void StateEnPausa::render(Window &window, const float updateTickTime)
{
    StateEnJuego::instance()->render(window, 0.f);

    window.draw(*contenedorMenu);

    for(sf::Text* &opcion : *opciones)
        window.draw(*opcion);
}

StateEnPausa::StateEnPausa()
{
    id = ID_State::enPausa;

    inicializar();
}

StateEnPausa::~StateEnPausa()
{
    //dtor
}

void StateEnPausa::inicializar()
{
    fuente = new sf::Font();

    if (!fuente->loadFromFile("resources/Ticketing.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(-1);
    }

    seguirPartida = new sf::Text(sf::String("Continuar"), *fuente);
    guardarPartida = new sf::Text(sf::String("Guardar Partida"), *fuente);
    salir = new sf::Text(sf::String("Salir"), *fuente);

    contenedorMenu = new sf::RectangleShape(sf::Vector2f(800.f*0.8f, 600.f*0.8f));

    contenedorMenu->setOrigin(contenedorMenu->getSize().x / 2.f, 0);
    contenedorMenu->setPosition(800.f/2.f, 600.f*0.1f);
    contenedorMenu->setFillColor(sf::Color(255, 255, 255, 127));
    contenedorMenu->setOutlineThickness(4.f);
    contenedorMenu->setOutlineColor(sf::Color::White);

    opciones = new std::vector<sf::Text*>();

    opciones->push_back(seguirPartida);
    opciones->push_back(guardarPartida);
    opciones->push_back(salir);

    fin = false;

    for(int i = 0; i < (int) opciones->size(); ++i)
    {
        opciones->at(i)->setOrigin(opciones->at(i)->getGlobalBounds().width / 2.f, 0);
        opciones->at(i)->setPosition(contenedorMenu->getPosition().x, 75.f + (100.f * (i+1)));
    }
}

void StateEnPausa::limpiar()
{
    seleccion = 0;
    update(0); // para que cuando entremos otra vez, haya hecho efecto el reinicio de los parametros iniciales
}
