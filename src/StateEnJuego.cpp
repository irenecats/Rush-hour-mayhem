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
        State::tiempoPlayeado = mVictoria.getPlayingOffset();
        mVictoria.stop();
    }
    else if(teclaPulsada == sf::Keyboard::Space && ruta->getActiva() && ruta->getDiagActual()==1)
    {
        reloj.restart();
        ruta->pasarDialogo();
    }
    else if(teclaPulsada == sf::Keyboard::O)
    {
        // reloj.restart();
        //ruta->haLlegado();
       // encuentraCMC();

    } /*else if(teclaPulsada == sf::Keyboard::B && ruta->getActiva() && ruta->getDiagActual()==0) {
        reloj.restart();
        ruta->setDiagActual(2);
    }*/
    return next_state;
}

void StateEnJuego::update(int tiempo)
{

    // update del estado enJuego
    recalculaRango();
    int eliminados = compruebaNPC();

    if(npcs.size() + eliminados > 10){
        generaCoches(eliminados);
    }
    else{

        generaCoches(20 - int(npcs.size()));
    }/*
    if (npcs.size() < 1) {
        generaCoches(1);
    }*/

    //detectColisioncNPC();

    ruta->Update(reloj);
    Jugador::instancia()->update(tiempo);
    detectColisionMapa();
    detectColisionRuta();
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->update(tiempo);
    if(ruta->getActiva())
    {
        Jugador::instancia()->updateBrujula(ruta->getDestino()->getPosition().x,
                                            ruta->getDestino()->getPosition().y);

        if(!cancionCambiada && !ruta->getTerminada()) {
            mTiempoLibre.stop();
            mMision.play();
            cancionCambiada = true;
        }
    }
    else
    {
        Jugador::instancia()->updateBrujula(ruta->getOrigen()->getPosition().x,
                                            ruta->getOrigen()->getPosition().y);
    }

    // Update de los npcs
    for(int i = 0; i<npcs.size(); i++) {
        bool tocaFrenar = false;
        for(int j = 0; !tocaFrenar && j<npcs.size(); j++) {
            if (i == j) {
                if (Collision::BoundingBoxSpriteRectTest(Jugador::instancia()->getJugador().getSprite(), npcs[i].GetRectFrenado())) {
                    tocaFrenar = true;
                }
            } else if (Collision::BoundingBoxSpriteRectTest(npcs[j].Getsprite().getSprite(), npcs[i].GetRectFrenado())) {
                tocaFrenar = true;
            }
        }
        if (tocaFrenar) {
            npcs[i].frenar();
        } else {
            npcs[i].velocidadNormal();
        }
        npcs[i].update(67); //TODO: ayuda
    }
}

void StateEnJuego::render(Window &window, const float updateTickTime)
{
    Jugador::instancia()->interpolar(updateTickTime);
    Camara::instancia()->centrarVista();
    window.setView(Camara::instancia()->getCarView());

    Mapa::Instance()->renderMapaAbajo(window);
    ruta->RenderPuntos(window);
    if(Jugador::instancia()->muestroGuia()){
        window.draw(guia);
    }
    Jugador::instancia()->dibujar(window);
    if(Jugador::instancia()->disparando()) Jugador::instancia()->getBala()->render(window, updateTickTime);
    for(unsigned int i = 0; i<npcs.size(); i++)
    {
        npcs[i].render(window, updateTickTime);
    }
    Mapa::Instance()->renderMapaArriba(window);
    Jugador::instancia()->renderBrujula(window, updateTickTime);
    window.setView(Camara::instancia()->getFullView());
    ruta->RenderDialogos(window);
    //GUI

    if(ruta->getTerminada())    window.draw(finRuta);
    //std::cout<<"Tamaño "<<guia.getVertexCount()<<std::endl;

}

StateEnJuego::StateEnJuego()
{
    id = ID_State::enJuego;
    nodos = Mapa::Instance()->getGrafo();

    mTiempoLibre.play();
    //printf("busco los nodos cercanos y genero coches ahi\n");
    buscaCercanos();
    generaCoches(1);
}

void StateEnJuego::nuevaPartida()
{
    ruta = factoriaRuta.creaRuta(1);
    origen = ruta->getOrigen();
    destino = ruta->getDestino();
    std::cout<<"Estado ruta: "<<ruta->getActiva()<<std::endl;

    if(!posInicialJugador)
        posInicialJugador = Jugador::instancia()->getJugador().getPosition();

    Jugador::instancia()->getJugador().setPosition(posInicialJugador[0], posInicialJugador[1]);

    fuente = sf::Font();
    if (!fuente.loadFromFile("resources/Ticketing.ttf"))
    {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    finRuta = sf::Text("Pulsa ENTER para ver tu puntuacion", fuente, 20);
    finRuta.setOrigin(finRuta.getGlobalBounds().width/2,finRuta.getGlobalBounds().height/2);
    finRuta.setColor(sf::Color::White);
    finRuta.setPosition(400, 375);
    guia = sf::VertexArray(sf::TrianglesStrip);
}

void StateEnJuego::cargarPartida()
{
    std::ifstream fichero("./resources/partidaGuardada.txt");
    std::string linea = "";

    int idRuta = 1;
    int pw = Jugador::instancia()->getPW();
    int dinero = Jugador::instancia()->getDinero();

    std::cout << "Vamos a leer el contenido del fichero tras recoger la idRuta, pw y dinero del jugador" << std::endl;

    if(getline(fichero, linea))
        idRuta = std::stoi(linea);
    if(getline(fichero, linea))
        pw = std::stoi(linea);
    if(getline(fichero, linea))
        dinero = std::stoi(linea);

    std::cout << "Hemos leido el contenido correctamente" << std::endl;

    Jugador::instancia()->setPowerUp(pw);
    Jugador::instancia()->setDinero(dinero);

    std::cout << "Set powerup y dinero del jugador" << std::endl;
    std::cout << "Ruta = " << idRuta << ", pw = " << pw << ", dinero = " << dinero << std::endl;

    ruta = factoriaRuta.creaRuta(idRuta);

    std::cout << "Acabamos de crear la ruta con factoriaRuta.creaRuta(idRuta)" << std::endl;

    origen = ruta->getOrigen();
    destino = ruta->getDestino();
    std::cout<<"Estado ruta: "<<ruta->getActiva()<<std::endl;

    if(!posInicialJugador)
        posInicialJugador = Jugador::instancia()->getJugador().getPosition();

    Jugador::instancia()->getJugador().setPosition(posInicialJugador[0], posInicialJugador[1]);

    fuente = sf::Font();
    if (!fuente.loadFromFile("resources/Ticketing.ttf"))
    {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    finRuta = sf::Text("Pulsa ENTER para ver tu puntuacion", fuente, 20);
    finRuta.setOrigin(finRuta.getGlobalBounds().width/2,finRuta.getGlobalBounds().height/2);
    finRuta.setColor(sf::Color::White);
    finRuta.setPosition(400, 375);
    guia = sf::VertexArray(sf::TrianglesStrip);
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
        npcs.push_back(NPC(cercanos[num], &iaCirc));
        npcs.back().setPosicionesIniciales();
        i++;
    }
    //printf("Tamanyo tras generar %i\n",npcs.size());
}

int StateEnJuego::compruebaNPC()
{
    int eliminados = 0;
    int distancia = 0;
    unsigned int i = 0;

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
    for(unsigned int i=0; i<nodos.size(); i++)
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
            dibujaGuia();
        }
    }
    else
    {
        if (!ruta->getTerminada() && Collision::BoundingBoxSpriteRectTest(Jugador::instancia()->getJugador().getSprite(),*destino))
        {
            ruta->haTerminado();
            guia = sf::VertexArray(sf::TrianglesStrip);
            //Cuando coche choque con ruta->getDestino,
            // delete ruta; rura = nullptr;
            mMision.stop();
            mVictoria.play();
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

                if(daux==0 || daux > distancia)
                {
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

    if(cercanos.size()<5)
    {
        // printf("Busco cercanos por que no tengo casi \n");
        buscaCercanos();
    }
    //printf("Recalculo los nodos\n");
    for(unsigned int i=0; i<cercanos.size(); i++)
    {
        // std::cout<<"I = "<<i<<std::endl;
        //std::cout<<"Coord Cercanos"<<cercanos[i]->getCoorX()<<" - "<<cercanos[i]->getCoorY()<<std::endl;
        //std::cout<<"Coord Coche"<<Jugador::instancia()->getJugador().getPosition()[0]<<" - "<<Jugador::instancia()->getJugador().getPosition()[1]<<std::endl;
        distancia = int(abs(cercanos[i]->getCoorX() - Jugador::instancia()->getJugador().getPosition()[0]));
        distancia += abs(cercanos[i]->getCoorY() - Jugador::instancia()->getJugador().getPosition()[1]);
        //Distancia discreta en geometria del taxista (distancia Manhattan)
        if(distancia < 1500 && distancia > 800)
        {
            cercaAux.push_back(cercanos[i]);
        }


        if(cercanos.size()<30)
        {
            hijos= cercanos[i]->adj;
            for(unsigned int j=0; j < hijos.size(); j++)
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

bool StateEnJuego::getRuta()
{
    if(ruta->getID() >= 5)//la ultima ruta
        return true;
    else
        return false;
}

void StateEnJuego::inicializar()
{
    ruta = factoriaRuta.creaRuta(ruta->getID()+1);
    mTiempoLibre.play();
    cancionCambiada = false;
}

void StateEnJuego::limpiar()
{

    int var = cercanos.size();
    printf("Tamanyo final %i\n", var);
}

void StateEnJuego::dibujaGuia(){
std::vector<sf::Vector2f> lineaRuta = ruta->getGuia();
sf::Vector2f player(Jugador::instancia()->getJugador().getPosition()[0],Jugador::instancia()->getJugador().getPosition()[1]);
float thickness = 5;

for(unsigned int i=1;i<lineaRuta.size();i++){
    sf::Vector2f  p0 = lineaRuta[i-1];
    sf::Vector2f  p1 = lineaRuta[i];
    sf::Vector2f line = p1 - p0;
    float separacion = sqrt((line.x*line.x) + (line.y*line.y));
    sf::Vector2f normal = sf::Vector2f( -line.y, line.x)/separacion;
    sf::Vector2f a = p0 - thickness * normal;
    sf::Vector2f b = p0 + thickness * normal;
    sf::Vector2f c = p1 - thickness * normal;
    sf::Vector2f d = p1 + thickness * normal;
    guia.append( sf::Vertex(a , sf::Color::Yellow));
    guia.append( sf::Vertex(b , sf::Color::Yellow));
    guia.append( sf::Vertex(c , sf::Color::Yellow));
    guia.append( sf::Vertex(d , sf::Color::Yellow));
}

}

/*
void StateEnJuego::encuentraCMC()
{
    printf("Busco CMC\n");
    int distancia=0;
    int mini=0;
    sf::Vector2f player(Jugador::instancia()->getJugador().getPosition()[0],Jugador::instancia()->getJugador().getPosition()[1]);

    float mindist= abs(nodos[0]->getCoorX() - player.x)+
                   abs(nodos[0]->getCoorY() - player.y);
    for(unsigned int i=0; i<nodos.size(); i++)
    {

        distancia = abs(nodos[i]->getCoorX() - player.x);
        distancia += abs(nodos[i]->getCoorY() - player.y);
        //Distancia discreta en geometria del taxista (distancia Manhattan)
        if(distancia<mindist)
        {
            mini=i;
            mindist = distancia;
            //printf("Disancia %i\n",distancia);
            //printf("Posicion %i - %i\n",nodos[i]->getCoorX(),nodos[i]->getCoorY());
            //cercanos.push_back(nodos[i]);
        }
    }
    //nodo origen
    Node* origin = nodos[mini];
    sf::Vector2f dest(226*32,349*32);
    std::vector<Node*> frontera;
    std::vector<Node*> interior;
    frontera.push_back(origin);


    while(frontera.size()>0)
    {
        mindist = frontera[0]->getDistancia(dest) + frontera[0]->getCoste();
        mini=0;
        for(unsigned int i=0; i<frontera.size(); i++)
        {
            //Distancia discreta en geometria del taxista (distancia Manhattan)
            distancia = frontera[i]->getDistancia(dest) + frontera[i]->getCoste();
            if( distancia < mindist)
            {
                mini=i;
                mindist = distancia;
                //printf("Disancia %i\n",distancia);
                //printf("Posicion %i - %i\n",nodos[i]->getCoorX(),nodos[i]->getCoorY());
                //cercanos.push_back(nodos[i]);
            }
        }
        interior.push_back(frontera[mini]);
        frontera.erase(frontera.begin()+mini);

        int num = interior.size()-1;
        for(unsigned int i =0; i<interior[num]->adj.size(); i++)
        {
            bool contr=false;
            int aux = -1;
            for(unsigned int j=0; j<frontera.size();j++){
                if(interior[num]->adj[j]->compare(frontera[j]) && aux ==-1){

                    contr = true;
                    aux = j;
                }
            }

            if(!contr)
            {
                //printf("\tExiste\n");
                frontera[mini]->adj[i]->setParent(interior[num]);
                frontera.push_back(interior[num]->adj[i]);
            }
            else{
                //printf("\t No existe\n");
                if(frontera[aux]->getCoste() > interior[num]->getCoste()+10){
                    frontera[aux]->setParent(interior[num]);
                }
            }ruta
        }

        if(frontera.size()<=0)
        {
            printf("Error \n");
            break;
        }
        else if(mindist<=800)
        {
            printf("Encontrado\n");
            std::cout<<interior[interior.size()-1]->getCoorX()<<" - "<<interior[interior.size()-1]->getCoorY()<<std::endl;
            bool contr=false;
                Nodo* fin = frontera[mini];
            while(!fin.getPadre()){
                sf::Vector2f  p0(fontera[mini]->getCoorX(),fontera[mini]->getCoorY());
                sf::Vector2f  p1(fontera[mini]->getParent,fontera[mini]);
                float thickness = 5;

                sf::Vector2f line = p1 - p0;
                float separacion = sqrt((line.x*line.x) + (line.y*line.y));
                sf::Vector2f normal = sf::Vector2f( -line.y, line.x)/separacion;
                sf::Vector2f a = p0 - thickness * normal;
                sf::Vector2f b = p0 + thickness * normal;
                sf::Vector2f c = p1 - thickness * normal;
                sf::Vector2f d = p1 + thickness * normal;

                Vector2f tangent = ((p2-p1).normalized() + (p1-p0).normalized()).normalized();
                Vector2f miter = Vector2f( -tangent.y, tangent.x ); //normal of the tangent

                float length = thickness / miter.dot( normal );

                Vector2f m1 = p1 - length * miter;
                Vector2f m2 = p1 + length * miter;

                guia.append( sf::Vertex(a , sf::Color::Red));
                guia.append( sf::Vertex(b , sf::Color::Red));
                guia.append( sf::Vertex(c , sf::Color::Red));
                guia.append( sf::Vertex(d , sf::Color::Red));
                //}
        }

        std::cout<<frontera.size()<<std::endl;
        if(frontera.size()>0)
        std::cout<<frontera[0]->getCoorX()<<" - "<<frontera[0]->getCoorY()<<std::endl;
        std::cout<<interior.size()<<std::endl;

>>>>>>> Stashed changes

    }

}
<<<<<<< Updated upstream
=======
void StateEnJuego::dibujaGuia(){
std::vector<sf::Vector2f> lineaRuta = ruta->getGuia();
sf::Vector2f player(Jugador::instancia()->getJugador().getPosition()[0],Jugador::instancia()->getJugador().getPosition()[1]);
float thickness = 5;

for(unsigned int i=1;i<lineaRuta.size();i++){
    sf::Vector2f  p0 = lineaRuta[i-1];
    sf::Vector2f  p1 = lineaRuta[i];
    sf::Vector2f line = p1 - p0;
    float separacion = sqrt((line.x*line.x) + (line.y*line.y));
    sf::Vector2f normal = sf::Vector2f( -line.y, line.x)/separacion;
    sf::Vector2f a = p0 - thickness * normal;
    sf::Vector2f b = p0 + thickness * normal;
    sf::Vector2f c = p1 - thickness * normal;
    sf::Vector2f d = p1 + thickness * normal;
    guia.append( sf::Vertex(a , sf::Color::Blue));
    guia.append( sf::Vertex(b , sf::Color::Blue));
    guia.append( sf::Vertex(c , sf::Color::Blue));
    guia.append( sf::Vertex(d , sf::Color::Blue));
}

}

/*
void StateEnJuego::encuentraCMC()
{
    printf("Busco CMC\n");
    int distancia=0;
    int mini=0;
    sf::Vector2f player(Jugador::instancia()->getJugador().getPosition()[0],Jugador::instancia()->getJugador().getPosition()[1]);

    float mindist= abs(nodos[0]->getCoorX() - player.x)+
                   abs(nodos[0]->getCoorY() - player.y);
    for(unsigned int i=0; i<nodos.size(); i++)
    {

        distancia = abs(nodos[i]->getCoorX() - player.x);
        distancia += abs(nodos[i]->getCoorY() - player.y);
        //Distancia discreta en geometria del taxista (distancia Manhattan)
        if(distancia<mindist)
        {
            mini=i;
            mindist = distancia;
            //printf("Disancia %i\n",distancia);
            //printf("Posicion %i - %i\n",nodos[i]->getCoorX(),nodos[i]->getCoorY());
            //cercanos.push_back(nodos[i]);
        }
    }
    //nodo origen
    Node* origin = nodos[mini];
    sf::Vector2f dest(226*32,349*32);
    std::vector<Node*> frontera;
    std::vector<Node*> interior;
    frontera.push_back(origin);


    while(frontera.size()>0)
    {
        mindist = frontera[0]->getDistancia(dest) + frontera[0]->getCoste();
        mini=0;
        for(unsigned int i=0; i<frontera.size(); i++)
        {
            //Distancia discreta en geometria del taxista (distancia Manhattan)
            distancia = frontera[i]->getDistancia(dest) + frontera[i]->getCoste();
            if( distancia < mindist)
            {
                mini=i;
                mindist = distancia;
                //printf("Disancia %i\n",distancia);
                //printf("Posicion %i - %i\n",nodos[i]->getCoorX(),nodos[i]->getCoorY());
                //cercanos.push_back(nodos[i]);
            }
        }
        interior.push_back(frontera[mini]);
        frontera.erase(frontera.begin()+mini);

        int num = interior.size()-1;
        for(unsigned int i =0; i<interior[num]->adj.size(); i++)
        {
            bool contr=false;
            int aux = -1;
            for(unsigned int j=0; j<frontera.size();j++){
                if(interior[num]->adj[j]->compare(frontera[j]) && aux ==-1){

                    contr = true;
                    aux = j;
                }
            }

            if(!contr)
            {
                //printf("\tExiste\n");
                frontera[mini]->adj[i]->setParent(interior[num]);
                frontera.push_back(interior[num]->adj[i]);
            }
            else{
                //printf("\t No existe\n");
                if(frontera[aux]->getCoste() > interior[num]->getCoste()+10){
                    frontera[aux]->setParent(interior[num]);
                }
            }
        }

        if(frontera.size()<=0)
        {
            printf("Error \n");
            break;
        }
        else if(mindist<=800)
        {
            printf("Encontrado\n");
            std::cout<<interior[interior.size()-1]->getCoorX()<<" - "<<interior[interior.size()-1]->getCoorY()<<std::endl;
            bool contr=false;
                Nodo* fin = frontera[mini];
            while(!fin.getPadre()){
                sf::Vector2f  p0(fontera[mini]->getCoorX(),fontera[mini]->getCoorY());
                sf::Vector2f  p1(fontera[mini]->getParent,fontera[mini]);
                float thickness = 5;

                sf::Vector2f line = p1 - p0;
                float separacion = sqrt((line.x*line.x) + (line.y*line.y));
                sf::Vector2f normal = sf::Vector2f( -line.y, line.x)/separacion;
                sf::Vector2f a = p0 - thickness * normal;
                sf::Vector2f b = p0 + thickness * normal;
                sf::Vector2f c = p1 - thickness * normal;
                sf::Vector2f d = p1 + thickness * normal;

                Vector2f tangent = ((p2-p1).normalized() + (p1-p0).normalized()).normalized();
                Vector2f miter = Vector2f( -tangent.y, tangent.x ); //normal of the tangent

                float length = thickness / miter.dot( normal );

                Vector2f m1 = p1 - length * miter;
                Vector2f m2 = p1 + length * miter;

                guia.append( sf::Vertex(a , sf::Color::Red));
                guia.append( sf::Vertex(b , sf::Color::Red));
                guia.append( sf::Vertex(c , sf::Color::Red));
                guia.append( sf::Vertex(d , sf::Color::Red));
                //}
        }

        std::cout<<frontera.size()<<std::endl;
        if(frontera.size()>0)
        std::cout<<frontera[0]->getCoorX()<<" - "<<frontera[0]->getCoorY()<<std::endl;
        std::cout<<interior.size()<<std::endl;


    }

}
*/
