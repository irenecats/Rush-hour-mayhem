#include "StateManager.h"

State* StateManager::estadoActual = nullptr;

StateManager::StateManager()
{

}

StateManager::~StateManager()
{

}

void StateManager::input(int teclaPulsada)
{
    if(!estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual es nulo al intentar acceder a input()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->input(teclaPulsada))
        {
            case ID_State::inicio :
                iniciar();
                break;

            case ID_State::enJuego :
                jugar();
                break;

            case ID_State::enPausa :
                pausar();
                break;
        }
    }
}

void StateManager::iniciar()
{
    if(!estadoActual)
    {
        estadoActual = StateInicio::instance();
        std::cout << "Estado actual es ahora: inicio" << std::endl;
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                //no debe pasar nada
                break;

            case ID_State::enJuego :
                std::cout << "Error en StateManager. El estado actual es enJuego al intentar acceder a iniciar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPausa :
                std::cout << "Error en StateManager. El estado actual es enPausa al intentar acceder a iniciar()" << std::endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
}

void StateManager::jugar()
{
    if(!estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual es nulo al intentar acceder a jugar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                //estadoActual = StateEnJuego::instance();
                //std::cout << "Estado actual es ahora: enJuego" << std::endl;
                break;

            case ID_State::enJuego :
                //no debe pasar nada
                break;

            case ID_State::enPausa :
                //estadoActual = StateEnJuego::instance();
                //std::cout << "Estado actual es ahora: enJuego" << std::endl;
                break;
        }
    }
}

void StateManager::pausar()
{
    if(!estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual es nulo al intentar acceder a pausar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                std::cout << "Error en StateManager. El estado actual es inicio al intentar acceder a pausar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enJuego :
                //estadoActual = StateEnPausa::instance(); // si estoy en juego, pongo el juego en pausa
                //std::cout << "Estado actual es ahora: enPausa" << std::endl;
                break;

            case ID_State::enPausa :
                //estadoActual = StateEnJuego::instance(); // si ya estoy en pausa, entiendo que quiero reanudar el juego
                //std::cout << "Estado actual es ahora: enJuego" << std::endl;
                break;
        }
    }
}

void StateManager::update()
{
    if(!estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual es nulo al intentar acceder a update()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        estadoActual->update();
    }
}

void StateManager::render(Window& window, const float updateTickTime)
{
    if(!estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual es nulo al intentar acceder a render()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        estadoActual->render(window, updateTickTime);
    }
}
