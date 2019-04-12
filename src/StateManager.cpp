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
        std::cout << "StateManager::input(): Error en StateManager. El estado actual es nulo al intentar acceder a input()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        ID_State next_state = estadoActual->input(teclaPulsada);

        if(estadoActual->getID() != next_state)
        {
            switch(next_state)
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

                case ID_State::enPuntuacion :
                    puntuar();
                    break;

                case ID_State::enTienda :
                    comprar();
                    break;
            }
        }
    }
}

void StateManager::iniciar()
{
    if(!estadoActual)
    {
        estadoActual = StateInicio::instance();
        std::cout << "StateManager::iniciar(): Estado actual es ahora: inicio" << std::endl;
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                //no debe pasar nada
                break;

            case ID_State::enJuego :
                std::cout << "StateManager::iniciar(): Error en StateManager. El estado actual es enJuego al intentar acceder a iniciar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPausa :
                std::cout << "StateManager::iniciar(): Error en StateManager. El estado actual es enPausa al intentar acceder a iniciar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPuntuacion :
                std::cout << "StateManager::iniciar(): Error en StateManager. El estado actual es enPuntuacion al intentar acceder a iniciar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enTienda :
                std::cout << "StateManager::iniciar(): Error en StateManager. El estado actual es enTienda al intentar acceder a iniciar()" << std::endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
}

void StateManager::jugar()
{
    if(!estadoActual)
    {
        std::cout << "StateManager::jugar(): Error en StateManager. El estado actual es nulo al intentar acceder a jugar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                estadoActual = StateEnJuego::instance(); // cambiamos el estado de inicio a enJuego
                std::cout << "StateManager::jugar(): Estado actual es ahora: enJuego" << std::endl;
                break;

            case ID_State::enJuego :
                // no debe pasar nada
                break;

            case ID_State::enPausa :
                estadoActual = StateEnJuego::instance(); // si ya estoy en pausa, entiendo que quiero reanudar el juego
                std::cout << "StateManager::jugar(): Estado actual es ahora: enJuego" << std::endl;
                break;

            case ID_State::enPuntuacion :
                std::cout << "StateManager::jugar(): Error en StateManager. El estado actual es enPuntuacion al intentar acceder a jugar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enTienda :
                estadoActual = StateEnJuego::instance();
                std::cout << "StateManager::jugar(): Estado actual es ahora: enJuego" << std::endl;
                break;
        }
    }
}

void StateManager::pausar()
{
    if(!estadoActual)
    {
        std::cout << "StateManager::pausar(): Error en StateManager. El estado actual es nulo al intentar acceder a pausar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                std::cout << "StateManager::pausar(): Error en StateManager. El estado actual es inicio al intentar acceder a pausar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enJuego :
                estadoActual = StateEnPausa::instance(); // si estoy en juego, pongo el juego en pausa
                std::cout << "StateManager::pausar(): Estado actual es ahora: enPausa" << std::endl;
                break;

            case ID_State::enPausa :
                //no debe pasar nada
                break;

            case ID_State::enPuntuacion :
                std::cout << "StateManager::pausar(): Error en StateManager. El estado actual es enPuntuacion al intentar acceder a pausar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enTienda :
                std::cout << "StateManager::pausar(): Error en StateManager. El estado actual es enTienda al intentar acceder a pausar()" << std::endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
}

void StateManager::puntuar()
{
    if(!estadoActual)
    {
        std::cout << "StateManager::puntuar(): Error en StateManager. El estado actual es nulo al intentar acceder a puntuar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                std::cout << "StateManager::puntuar(): Error en StateManager. El estado actual es inicio al intentar acceder a puntuar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enJuego :
                estadoActual = StateEnPuntuacion::instance();
                std::cout << "StateManager::puntuar(): Estado actual es ahora: enPuntuacion" << std::endl;
                break;

            case ID_State::enPausa :
                std::cout << "StateManager::puntuar(): Error en StateManager. El estado actual es enPausa al intentar acceder a puntuar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPuntuacion :
                //no debe pasar nada
                break;

            case ID_State::enTienda :
                std::cout << "StateManager::puntuar(): Error en StateManager. El estado actual es enTienda al intentar acceder a puntuar()" << std::endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
}

void StateManager::comprar()
{
    if(!estadoActual)
    {
        std::cout << "StateManager::comprar(): Error en StateManager. El estado actual es nulo al intentar acceder a comprar()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        switch(estadoActual->getID())
        {
            case ID_State::inicio :
                std::cout << "StateManager::comprar(): Error en StateManager. El estado actual es inicio al intentar acceder a comprar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enJuego :
                std::cout << "StateManager::comprar(): Error en StateManager. El estado actual es enJuego al intentar acceder a comprar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPausa :
                std::cout << "StateManager::comprar(): Error en StateManager. El estado actual es enPausa al intentar acceder a comprar()" << std::endl;
                exit(EXIT_FAILURE);
                break;

            case ID_State::enPuntuacion :
                estadoActual = StateEnTienda::instance();
                std::cout << "StateManager::comprar(): Estado actual es ahora enTienda" << std::endl;
                break;

            case ID_State::enTienda :
                //no debe pasar nada
                break;
        }
    }
}

void StateManager::update()
{
    if(!estadoActual)
    {
        std::cout << "StateManager::update(): Error en StateManager. El estado actual es nulo al intentar acceder a update()" << std::endl;
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
        std::cout << "StateManager::render(): Error en StateManager. El estado actual es nulo al intentar acceder a render()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        estadoActual->render(window, updateTickTime);
    }
}
