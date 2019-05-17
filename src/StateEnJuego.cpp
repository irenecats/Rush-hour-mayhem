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
    else if(ruta->getTerminada() && teclaPulsada == sf::Keyboard::Return)
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
    recalculaRango();
    int eliminados = compruebaNPC();
    if(npcs.size() + eliminados > 10){
        generaCoches(eliminados);
    }
    else{

        generaCoches(20 - int(npcs.size()));
    }

    //detectColisioncNPC();

    ruta->Update(reloj);
    Jugador::instancia()->update();
    detectColisionMapa();
    detectColisionRuta();
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->update();
    if(ruta->getActiva())
    {
        Jugador::instancia()->updateBrujula(ruta->getDestino()->getPosition().x,
                                            ruta->getDestino()->getPosition().y);
    }
    else
    {
        Jugador::instancia()->updateBrujula(ruta->getOrigen()->getPosition().x,
                                            ruta->getOrigen()->getPosition().y);
    }
}

void StateEnJuego::render(Window &window, const float updateTickTime)
{
    Jugador::instancia()->interpolar(updateTickTime);
    Camara::instancia()->centrarVista();
    window.setView(Camara::instancia()->getCarView());

    Mapa::Instance()->renderMapaAbajo(window);
    ruta->RenderPuntos(window);

    Jugador::instancia()->dibujar(window);
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->render(window, updateTickTime);
    Mapa::Instance()->renderMapaArriba(window);
    Jugador::instancia()->renderBrujula(window, updateTickTime);

    for(int i = 0; i<npcs.size(); i++)
    {
        npcs[i].render(window,1);
    }

    window.setView(Camara::instancia()->getFullView());
    ruta->RenderDialogos(window);
    //GUI
    if(ruta->getTerminada())    window.draw(finRuta);
}

StateEnJuego::StateEnJuego()
{
    id = ID_State::enJuego;
    nodos = Mapa::Instance()->getGrafo();

    //printf("busco los nodos cercanos y genero coches ahi\n");
    buscaCercanos();
    generaCoches(20);

    ruta = factoriaRuta.creaRuta(1);
    origen = ruta->getOrigen();
    destino = ruta->getDestino();
    std::cout<<"Estado ruta: "<<ruta->getActiva()<<std::endl;


    fuente = sf::Font();
    if (!fuente.loadFromFile("resources/Ticketing.ttf"))
    {
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

void StateEnJuego::generaCoches(int tot)
{
    //printf("Genero %i coches",tot);
    int num = 0, i=0,mx = cercanos.size();
   // std::vector<Node*>   usados;

    bool contr = false;
    //printf("Tamanyo antes de generar %i\n",npcs.size());
    while(i<tot && cercanos.size()>1)
    {
        num = (0 + (rand() % (int)(mx)));
        contr = false;
            npcs.push_back(NPC(*cercanos[num]));
            i++;
    }
    //printf("Tamanyo tras generar %i\n",npcs.size());
}

int StateEnJuego::compruebaNPC()
{
    int eliminados = 0;
    int distancia = 0;
    int i = 0;

    while(i<npcs.size())
    {

        distancia = int(abs(npcs[i].Getsprite().getPosition()[0] - Jugador::instancia()->getJugador().getPosition()[0]));
        //printf("Sprite %f - %f\n",npcs[i].Getsprite().getPosition()[0] , npcs[i].Getsprite().getPosition()[1]);
        //printf("Jugador %f - %f\n",Jugador::instancia()->getJugador().getPosition()[0], Jugador::instancia()->getJugador().getPosition()[1]);
        //printf("Dist coche %i\n",distancia);
        distancia +=abs(npcs[i].Getsprite().getPosition()[1] - Jugador::instancia()->getJugador().getPosition()[1]);
        //Distancia discreta en geometria del taxista (distancia Manhattan)
        //printf("Creado en %i - %i\n",npcs[i].Getsprite().getPosition()[0],npcs[i].Getsprite().getPosition()[1]);
        if(distancia>1500)
        {
            /*printf("!!%i\n",i);
            printf("Eimino\n");
            printf("TAM %i\n", int(npcs.size()));
            printf("----\n");*/

            npcs.erase(npcs.begin()+i);
            eliminados++;
            //eliminapos.push_back(i);

        }
        else
        {
            //printf("no elimino\n");
            i++;
        }

    }
    //printf("TAM despues de eliminar %i\n", int(npcs.size()));
    return eliminados;

}

void StateEnJuego::buscaCercanos()
{
    int distancia=0;
    for(int i=0; i<nodos.size(); i++)
    {

        distancia = abs(nodos[i]->getCoorX() - Jugador::instancia()->getJugador().getPosition()[0]);
        distancia += abs(nodos[i]->getCoorY() - Jugador::instancia()->getJugador().getPosition()[1]);
        //Distancia discreta en geometria del taxista (distancia Manhattan)
        if(distancia<2000)
        {
            //printf("Disancia %i\n",distancia);
            //printf("Posicion %i - %i\n",nodos[i]->getCoorX(),nodos[i]->getCoorY());
            cercanos.push_back(nodos[i]);
        }
    }
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
{
    //Cojo los tiles cercanos
    int         tilex = Jugador::instancia()->getJugador().getPosition()[0]/32;
    int         tiley = Jugador::instancia()->getJugador().getPosition()[1]/32;
    Sprite****  mapa  = Mapa::Instance()->getMapa();
    int         my    = std::min(Mapa::Instance()->getHeight(), tiley +3);
    int         mx    = std::min(Mapa::Instance()->getWidth(), tilex +3);
    int cont = 0;
    float colx, coly, xx, yy;
    float distancia, daux;

    daux=0;

    tilex = std::max(0,tilex - 3);
    tiley = std::max(0,tiley -3);

    for(int y=tiley; y<my; y++)
    {
        for(int x=tilex; x<mx; x++)
        {
            //detecto si colisiona y hago que no se mueva
            if(mapa[Mapa::Instance()->getNumlayer()-1][y][x]!=NULL && Collision::BoundingBoxTest(mapa[Mapa::Instance()->getNumlayer()-1][y][x]->getSprite(), Jugador::instancia()->getJugador().getSprite()))
            {
                cont++;
                colx = mapa[Mapa::Instance()->getNumlayer()-1][y][x]->getPosition()[0];
                coly = mapa[Mapa::Instance()->getNumlayer()-1][y][x]->getPosition()[1];

                distancia = sqrt((colx - coly)*(colx - coly) +
                   (Jugador::instancia()->getJugador().getPosition()[0] - Jugador::instancia()->getJugador().getPosition()[1])*(Jugador::instancia()->getJugador().getPosition()[0] - Jugador::instancia()->getJugador().getPosition()[1]));

                if(daux==0 || daux > distancia){
                    daux = distancia;
                    xx = colx;
                    yy = coly;
                }

            }
        }
    }



    if(cont>0) Jugador::instancia()->frenar(xx, yy);
    else Jugador::instancia()->nofrenar();
}

void StateEnJuego::recalculaRango()
{
    int distancia = 0;
    std::vector<Node*> hijos;
    std::vector<Node*> cercaAux;

    if(cercanos.size()<5){
       // printf("Busco cercanos por que no tengo casi \n");
        buscaCercanos();
    }
    //printf("Recalculo los nodos\n");
    for(int i=0; i<cercanos.size(); i++)
    {
       // std::cout<<"I = "<<i<<std::endl;
        //std::cout<<"Coord Cercanos"<<cercanos[i]->getCoorX()<<" - "<<cercanos[i]->getCoorY()<<std::endl;
        //std::cout<<"Coord Coche"<<Jugador::instancia()->getJugador().getPosition()[0]<<" - "<<Jugador::instancia()->getJugador().getPosition()[1]<<std::endl;
        distancia = int(abs(cercanos[i]->getCoorX() - Jugador::instancia()->getJugador().getPosition()[0]));
        distancia += abs(cercanos[i]->getCoorY() - Jugador::instancia()->getJugador().getPosition()[1]);
        //Distancia discreta en geometria del taxista (distancia Manhattan)
        //printf("Distancia %i\n", distancia);
        if(distancia < 1500 && distancia > 800)
        {
            cercaAux.push_back(cercanos[i]);
        }


        if(cercanos.size()<30)
        {
            hijos= cercanos[i]->adj;
            for(int j=0; j < hijos.size(); j++)
            {
                distancia = int(abs(hijos[j]->getCoorX() - Jugador::instancia()->getJugador().getPosition()[0]));
                distancia += abs(hijos[j]->getCoorY() - Jugador::instancia()->getJugador().getPosition()[1]);
                if(distancia < 1500 && distancia > 800)
                {
                    cercaAux.push_back(hijos[j]);
                }
            }
        }
    }
    cercanos = cercaAux;
}

bool StateEnJuego::getRuta(){
    if(ruta->getID() == 5)
        return true;
    else
        return false;
}

void StateEnJuego::inicializar()
{

}

void StateEnJuego::limpiar()
{

    int var = cercanos.size();
    printf("Tamanyo final %i\n", var);
}
