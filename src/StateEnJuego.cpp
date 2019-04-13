#include "StateEnJuego.h"
#include "Mapa.h"

StateEnJuego* StateEnJuego::instancia = nullptr;

StateEnJuego* StateEnJuego::instance()
{
    if(!instancia)
        instancia = new StateEnJuego;

    return instancia;
}

ID_State StateEnJuego::input(int teclaPulsada)
{
    next_state = id;

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
    else if(teclaPulsada == sf::Keyboard::O)
    {
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
    detectColisionMapa();
    detectColisionRuta();
    ruta->Update(reloj);
    Jugador::instancia()->update();
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->update();
    Jugador::instancia()->updateBrujula(ruta->getDestino()->getPosition().x,
                                        ruta->getDestino()->getPosition().y);
}

void StateEnJuego::render(Window &window, const float updateTickTime)
{
    window.clear();

    Camara::instancia()->centrarVista();
    window.setView(Camara::instancia()->getCarView());

    Mapa::Instance()->renderMapaAbajo(window);
    ruta->RenderPuntos(window);
    Jugador::instancia()->render(window, 1);
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->render(window, 1);
    Mapa::Instance()->renderMapaArriba(window);
    Jugador::instancia()->renderBrujula(window, 1);

    window.setView(Camara::instancia()->getFullView());
    ruta->RenderDialogos(window);
    //Brujula
    //GUI
    window.display();
}

StateEnJuego::StateEnJuego()
{
    id = ID_State::enJuego;
    ruta = factoriaRuta.creaRuta(1);
    origen = ruta->getOrigen();
    destino = ruta->getDestino();
    std::cout<<"Estado ruta: "<<ruta->getActiva()<<std::endl;
}

StateEnJuego::~StateEnJuego()
{
    //dtor
}

void StateEnJuego::detectColisionRuta()
{
    if(!ruta->getActiva())
    {
        if (!ruta->getActiva() && Collision::BoundingBoxSpriteRectTest(Jugador::instancia()->getJugador().getSprite(),*origen) )
        {
            reloj.restart();
            ruta->haLlegado();
        }
    }
    else
    {
        if (!ruta->getTerminada() && Collision::BoundingBoxSpriteRectTest(Jugador::instancia()->getJugador().getSprite(),*destino))
        {
            ruta->haTerminado();
            printf("FIN DE LA RUTA\n");
        }
    }
}

void StateEnJuego::detectColisionMapa()
{   //Cojo los tiles cercanos
    int tilex=Jugador::instancia()->getJugador().getPosition()[0]/32;
    int tiley=Jugador::instancia()->getJugador().getPosition()[1]/32;

    mapa = Mapa::Instance()->getMapa();
    for(int y=0; y<Mapa::Instance()->getHeight(); y++)
    {
        for(int x=0; x<Mapa::Instance()->getWidth(); x++)
        {
                //detecto si colisiona y hago que no se mueva
                if(mapa[Mapa::Instance()->getNumlayer()-1][y][x]!=NULL && Collision::BoundingBoxTest(mapa[Mapa::Instance()->getNumlayer()-1][y][x]->getSprite(), Jugador::instancia()->getJugador().getSprite()))
                {

                }
        }
    }
}

