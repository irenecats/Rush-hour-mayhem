#include "StateManager.h"

State* StateManager::estadoActual = nullptr;

StateManager::StateManager()
{

}

StateManager::~StateManager()
{

}

void StateManager::iniciar()
{
    if(estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual NO es nulo al intentar acceder a iniciar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        estadoActual = StateInicio::instance();
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
            case ID_State::enJuego :
                std::cout << "Error en StateManager. El estado actual es enJuego al intentar acceder a jugar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPausa :
                //estadoActual = StateEnJuego::instance();
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
            case ID_State::enJuego :
                //estadoActual = StateEnPausa::instance(); // si estoy en juego, pongo el juego en pausa
                break;

            case ID_State::enPausa :
                //estadoActual = StateEnJuego::instance(); // si ya estoy en pausa, entiendo que quiero reanudar el juego
                break;
        }
    }
}

void StateManager::input()
{
    if(!estadoActual)
    {
        std::cout << "Error en StateManager. El estado actual es nulo al intentar acceder a input()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        estadoActual->input();
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
