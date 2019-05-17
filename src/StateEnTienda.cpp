#include "StateEnTienda.h"

StateEnTienda* StateEnTienda::instancia = nullptr;

StateEnTienda* StateEnTienda::instance()
{
    if(!instancia)
        instancia = new StateEnTienda;

    return instancia;
}

ID_State StateEnTienda::input(int teclaPulsada)
{
    next_state = id;

    if(teclaPulsada == sf::Keyboard::Return) {

        //Hay que comprobar que el jugador tenga dinero suficiente
        //toAnsiString() convierte sf::String a String y std::stoi convierte un string a int (activar [-std=c++11])
        if(Jugador::instancia()->getDinero() >= std::stoi(precios[seleccionado]->getString().toAnsiString())) {
            std::cout << "Se ha seleccionado el Power-Up " << powerUps[seleccionado]->getId() << std::endl;
            Jugador::instancia()->setPowerUp(powerUps[seleccionado]->getId());

            //Le restamos lo que vale
            Jugador::instancia()->setDinero(-powerUps[seleccionado]->getPrecio());
            std::cout << "Dinero restante: " << Jugador::instancia()->getDinero() << std::endl;

            limpiar();
            update(0);
            next_state = ID_State::enJuego;
            StateEnJuego::instance()->inicializar();

        } else {
            std::cout << "eres pobre no puedes" << std::endl;
        }
    }

    if(teclaPulsada == sf::Keyboard::Escape) {
        std::cout << "Has salido sin comprar nada" << std::endl;
        limpiar();
        update(0);
        next_state = ID_State::enJuego;
        StateEnJuego::instance()->inicializar();
    }

    if(teclaPulsada == sf::Keyboard::Right)
        seleccionado++;

    if(teclaPulsada == sf::Keyboard::Left)
        seleccionado--;

    return next_state;
}

void StateEnTienda::update(int tiempo)
{
    if(reiniciarTienda)
    {
        inicializar();
        reiniciarTienda = !reiniciarTienda;
    }

    if(seleccionado == -1)
        seleccionado = powerUps.size()-1;

    if(seleccionado > (int) (powerUps.size()-1))
        seleccionado = 0;


    recSeleccion->setPosition(powerUps[seleccionado]->getSpritePU()->getPosition()[0], powerUps[seleccionado]->getSpritePU()->getPosition()[1]);
    descrip->setString(descripciones[seleccionado]);
    nom->setString(nombres[seleccionado]);
}

void StateEnTienda::render(Window& window, const float updateTickTime)
{
    window.draw(*titulo);
    window.draw(*dineroJugador);
    window.draw(*precio1);
    window.draw(*precio2);
    window.draw(*precio3);
    window.draw(*recSeleccion);
    window.draw(*powerUps[0]->getSpritePU());
    window.draw(*powerUps[1]->getSpritePU());
    window.draw(*powerUps[2]->getSpritePU());
    window.draw(*ayudaPlayer);
    window.draw(*cajaDialogo);
    window.draw(*nom);
    window.draw(*descrip);
}

StateEnTienda::StateEnTienda()
{
    id = ID_State::enTienda;

    inicializar();
}


void StateEnTienda::configurarPowerUps(PowerUp*& pu, float n1, float n2) {
    pu->getSpritePU()->setOrigin(pu->getSpritePU()->getGlobalBounds()[0]/2, pu->getSpritePU()->getGlobalBounds()[1]/2);
    pu->getSpritePU()->setPosition(tamanyoX*n1 - 10, tamanyoY-tamanyoY*n2);
}


void StateEnTienda::configurarPrecios(sf::Text*& precio, int num, int numPowerUp) {

    precio = new sf::Text(std::to_string(num), *fuente, 30);
    precio->setColor(sf::Color::White);
    precio->setOrigin(precio->getGlobalBounds().width/2, precio->getGlobalBounds().height/2);
    precio->setPosition(powerUps[numPowerUp]->getSpritePU()->getPosition()[0],
                       powerUps[numPowerUp]->getSpritePU()->getPosition()[1] - powerUps[numPowerUp]->getSpritePU()->getGlobalBounds()[1]/2 - kMargen*2);

    precios.push_back(precio);
}


void StateEnTienda::configurarInfo(sf::Text*& tex, int tamanyo, float x, float y) {
    tex = new sf::Text(" ", *fuente, tamanyo);
    tex->setColor(sf::Color::White);
    tex->setPosition(x, y);
}


int StateEnTienda::numRandom(std::string tipoPowerUp) {
    int numero = 0;

    if(tipoPowerUp == "basico") {
        numero = (rand() % 4) + 1;
    }

    if(tipoPowerUp == "especial") {
        numero = 7 - (rand() % 2);
    }

    return numero;
}


StateEnTienda::~StateEnTienda()
{
    delete titulo;
    delete dineroJugador;
    delete precio1;
    delete precio2;
    delete precio3;
    delete recSeleccion;
    delete powerUps[0];
    delete powerUps[1];
    delete powerUps[2];
    delete ayudaPlayer;
    delete cajaDialogo;
    delete nom;
    delete descrip;
    delete fpu;
    delete fuente;
}

void StateEnTienda::inicializar()
{
    if(fuente)
        delete fuente;

    fuente = new sf::Font();

    if (!fuente->loadFromFile("resources/Ticketing.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    if(fpu)
        delete fpu;

    fpu = new FactoryPowerUp();

    //Para resetear la semilla hay que usar esto. Si no, se generan los mismos números aleatorios en cada ejecución.
    srand(time(NULL));
    int p1 = numRandom("basico");
    int p2 = numRandom("basico");
    int p3 = numRandom("especial");

    while(p2 == p1)
        p2 = numRandom("basico");

    std::cout << "Powerup 1: " << p1 << std::endl;
    std::cout << "Powerup 2: " << p2 << std::endl;
    std::cout << "Powerup 3: " << p3 << std::endl;

    std::cout << "Si powerups no esta vacio" << std::endl;
    if(!powerUps.empty())
        for(PowerUp* &pu : powerUps)
        {
            std::cout << "borro un powerup" << std::endl;
            delete pu;
        }

    std::cout << "limpiamos powerups" << std::endl;
    powerUps.clear();

    std::cout << "creamos un powerup" << std::endl;
    powerUps.push_back(fpu->crearPowerUp(p1));
    std::cout << "creamos un powerup" << std::endl;
    powerUps.push_back(fpu->crearPowerUp(p2));
    std::cout << "creamos un powerup" << std::endl;
    powerUps.push_back(fpu->crearPowerUp(p3));


    //Configurar los sprites de los power-ups
    std::cout << "configuramos un powerup" << std::endl;
    configurarPowerUps(powerUps[0], (float)1/4, (float)4.25/7);
    std::cout << "configuramos un powerup" << std::endl;
    configurarPowerUps(powerUps[1], (float)2/4, (float)4.25/7);
    std::cout << "configuramos un powerup" << std::endl;
    configurarPowerUps(powerUps[2], (float)3/4, (float)4.25/7);

    std::cout << "si existe recSeleccion lo borramos" << std::endl;
    if(recSeleccion)
        delete recSeleccion;
    std::cout << "creamos recSeleccion" << std::endl;
    //Este rectángulo se dibujará por detrás, y simulará un borde para el Sprite (para mostrar cuál está seleccionado)
    recSeleccion = new sf::RectangleShape(sf::Vector2f(powerUps[0]->getSpritePU()->getGlobalBounds()[0] + kMargen/2, powerUps[0]->getSpritePU()->getGlobalBounds()[1] + kMargen/2));
    recSeleccion->setOrigin(recSeleccion->getGlobalBounds().width/2, recSeleccion->getGlobalBounds().height/2);
    recSeleccion->setPosition(powerUps[0]->getSpritePU()->getPosition()[0], powerUps[0]->getSpritePU()->getPosition()[1]);
    recSeleccion->setFillColor(sf::Color(255, 230, 15));

    std::cout << "Si precios no esta vacio vamos a borrar sus textos" << std::endl;
    if(!precios.empty())
    {
        for(sf::Text* &texto : precios)
        {
            std::cout << "borramos un texto" << std::endl;
            delete texto;
        }
        precios.clear();
    }

    //Información de los Power-Ups
    std::cout << "configuramos un precio" << std::endl;
    configurarPrecios(precio1, powerUps[0]->getPrecio(), 0);
    std::cout << "configuramos un precio" << std::endl;
    configurarPrecios(precio2, powerUps[1]->getPrecio(), 1);
    std::cout << "configuramos un precio" << std::endl;
    configurarPrecios(precio3, powerUps[2]->getPrecio(), 2);

    std::cout << "si ya hay nombres los borramos" << std::endl;
    if(!nombres.empty())
        nombres.clear();

    std::cout << "obtenemos los nombres" << std::endl;
    nombres = {powerUps[0]->getNombre(), powerUps[1]->getNombre(), powerUps[2]->getNombre()};

    std::cout << "si ya hay descripciones las borramos" << std::endl;
    if(!descripciones.empty())
        descripciones.clear();

    std::cout << "obtenemos las descripciones" << std::endl;
    descripciones = {powerUps[0]->getDescripcion(), powerUps[1]->getDescripcion(), powerUps[2]->getDescripcion()};

    std::cout << "si ya existe el nombre y la descripcion principales los borramos" << std::endl;
    if(nom)
        delete nom;
    if(descrip)
        delete descrip;

    std::cout << "Configuro nombre" << std::endl;
    configurarInfo(nom, 30, 80, 450);
    std::cout << "Configuro descripcion" << std::endl;
    configurarInfo(descrip, 20, 90, 500);

    if(cajaDialogo)
        delete cajaDialogo;

    cajaDialogo = new Sprite(TexturaContainer::instancia()->getTextura("SpritesDialogos"));
    cajaDialogo->setRectTextura(sf::IntRect(0,128,800,250));
    cajaDialogo->setOrigin(cajaDialogo->getGlobalBounds()[0]/2,cajaDialogo->getGlobalBounds()[1]/2);
    cajaDialogo->setScale(0.9f, 0.6f);
    cajaDialogo->setPosition(400, 500);

    if(titulo)
        delete titulo;
    //Otros textos de la pantalla
    titulo = new sf::Text("Tienda de Power-Ups", *fuente, 40);
    titulo->setColor(sf::Color::White);
    titulo->setPosition(kMargen, kMargen);

    if(dineroJugador)
        delete dineroJugador;

    dineroJugador = new sf::Text("Dinero total: " + std::to_string(Jugador::instancia()->getDinero()), *fuente, 30);
    dineroJugador->setColor(sf::Color::White);
    dineroJugador->setPosition(tamanyoX - dineroJugador->getGlobalBounds().width - kMargen, kMargen);

    if(ayudaPlayer)
        delete ayudaPlayer;

    ayudaPlayer = new sf::Text("Pulsa ENTER para comprar un Power-Up\nPulsa ESC para salir de la tienda sin comprar", *fuente, 20);
    ayudaPlayer->setOrigin(ayudaPlayer->getGlobalBounds().width/2, ayudaPlayer->getGlobalBounds().height/2);
    ayudaPlayer->setColor(sf::Color::White);
    ayudaPlayer->setPosition(400, 375);
}

void StateEnTienda::limpiar()
{
    seleccionado = 0;
    dineroAhorrado = 200;

    reiniciarTienda = true;
}
