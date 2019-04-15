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

    // update del estado enJuego
    detectColisionMapa();
    detectColisionRuta();
    ruta->Update(reloj);
    Jugador::instancia()->update();
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->update();
    if(ruta->getActiva()){
        Jugador::instancia()->updateBrujula(ruta->getDestino()->getPosition().x,
                                        ruta->getDestino()->getPosition().y);
    }
    else{
         Jugador::instancia()->updateBrujula(ruta->getOrigen()->getPosition().x,
                                        ruta->getOrigen()->getPosition().y);
    }
}

void StateEnJuego::render(Window &window, const float updateTickTime)
{
    window.clear();

    Jugador::instancia()->interpolar(updateTickTime);
    Camara::instancia()->centrarVista();
    window.setView(Camara::instancia()->getCarView());

    Mapa::Instance()->renderMapaAbajo(window);
    ruta->RenderPuntos(window);
    Jugador::instancia()->dibujar(window);
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->render(window, updateTickTime);
    Mapa::Instance()->renderMapaArriba(window);
    Jugador::instancia()->renderBrujula(window, updateTickTime);

    window.setView(Camara::instancia()->getFullView());
    ruta->RenderDialogos(window);
    //GUI
    if(ruta->getTerminada())    window.draw(finRuta);
    window.display();
}

StateEnJuego::StateEnJuego()
{
    id = ID_State::enJuego;
    ruta = factoriaRuta.creaRuta(1);
    origen = ruta->getOrigen();
    destino = ruta->getDestino();
    std::cout<<"Estado ruta: "<<ruta->getActiva()<<std::endl;


    fuente = sf::Font();
    if (!fuente.loadFromFile("resources/Ticketing.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    finRuta = sf::Text("Pulsa G para ver tu puntuacion", fuente, 20);
    finRuta.setOrigin(finRuta.getGlobalBounds().width/2,finRuta.getGlobalBounds().height/2);
    finRuta.setColor(sf::Color::White);
    finRuta.setPosition(400, 375);
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
            //Cuando coche choque con ruta->getDestino,
            // delete ruta; rura = nullptr;
            printf("FIN DE LA RUTA\n");
        }
    }
}

void StateEnJuego::detectColisionMapa()
{   //Cojo los tiles cercanos
    int         tilex = Jugador::instancia()->getJugador().getPosition()[0]/32;
    int         tiley = Jugador::instancia()->getJugador().getPosition()[1]/32;
    Sprite****  mapa  = Mapa::Instance()->getMapa();
    int         my    = std::min(Mapa::Instance()->getHeight(), tiley +3);
    int         mx    = std::min(Mapa::Instance()->getWidth(), tilex +3);

    tilex = std::max(0,tilex - 3);
    tiley = std::max(0,tiley -3);

    for(int y=tiley; y<my; y++)
    {
        for(int x=tilex; x<mx; x++)
        {
                //detecto si colisiona y hago que no se mueva
                if(mapa[Mapa::Instance()->getNumlayer()-1][y][x]!=NULL && Collision::BoundingBoxTest(mapa[Mapa::Instance()->getNumlayer()-1][y][x]->getSprite(), Jugador::instancia()->getJugador().getSprite()))
                {

                }
        }
    }
}

