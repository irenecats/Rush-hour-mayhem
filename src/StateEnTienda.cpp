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
        if(dineroAhorrado >= std::stoi(precios[seleccionado]->getString().toAnsiString())) {
            std::cout << "Se ha seleccionado el Power-Up " << powerUps[seleccionado]->getId() << std::endl;
            Jugador::instancia()->setPowerUp(powerUps[seleccionado]->getId());
            next_state = ID_State::enJuego;

        } else {
            std::cout << "eres pobre no puedes" << std::endl;
        }
    }

    if(teclaPulsada == sf::Keyboard::Right)
        seleccionado++;

    if(teclaPulsada == sf::Keyboard::Left)
        seleccionado--;

    return next_state;
}

void StateEnTienda::update()
{
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
    window.clear();

    window.draw(*titulo);
    window.draw(*recSeleccion);
    window.draw(*precio1);
    window.draw(*precio2);
    window.draw(*precio3);
    window.draw(*dineroJugador);
    window.draw(cajaDialogo->getSprite());
    window.draw(*nom);
    window.draw(*descrip);
    window.draw(powerUps[0]->getSpritePU()->getSprite());
    window.draw(powerUps[1]->getSpritePU()->getSprite());
    window.draw(powerUps[2]->getSpritePU()->getSprite());

    window.display();
}

StateEnTienda::StateEnTienda()
{
    id = ID_State::enTienda;

    fpu = new FactoryPowerUp();

    //Para resetear la semilla hay que usar esto. Si no, se generan los mismos números aleatorios en cada ejecución.
    srand(time(NULL));

    int p1 = numRandom("basico");
    int p2 = numRandom("basico");
    int p3 = numRandom("especial");

    std::cout << "Powerup 1: " << p1 << std::endl;
    std::cout << "Powerup 2: " << p2 << std::endl;
    std::cout << "Powerup 3: " << p3 << std::endl;
    while(p2 == p1)
        p2 = numRandom("basico");

    powerUps.push_back(fpu->crearPowerUp(p1));
    powerUps.push_back(fpu->crearPowerUp(p2));
    powerUps.push_back(fpu->crearPowerUp(p3));


    fuente = new sf::Font();

    if (!fuente->loadFromFile("resources/Ticketing.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    titulo = new sf::Text("Tienda de Power-Ups", *fuente, 40);
    titulo->setColor(sf::Color::White);
    titulo->setPosition(kMargen, kMargen);


    //Configurar los sprites de los power-ups
    powerUps[0]->getSpritePU()->setOrigin(powerUps[0]->getSpritePU()->getGlobalBounds()[0]/2, powerUps[0]->getSpritePU()->getGlobalBounds()[1]/2);
    powerUps[0]->getSpritePU()->setScale(0.25, 0.3);
    powerUps[0]->getSpritePU()->setPosition(tamanyoX*(float)1/4 - 10, tamanyoY-tamanyoY*(float)4/7);

    powerUps[1]->getSpritePU()->setOrigin(powerUps[1]->getSpritePU()->getGlobalBounds()[0]/2, powerUps[1]->getSpritePU()->getGlobalBounds()[1]/2);
    powerUps[1]->getSpritePU()->setScale(0.25, 0.3);
    powerUps[1]->getSpritePU()->setPosition(tamanyoX*(float)2/4 - 10, tamanyoY-tamanyoY*(float)4/7);

    powerUps[2]->getSpritePU()->setOrigin(powerUps[2]->getSpritePU()->getGlobalBounds()[0]/2, powerUps[2]->getSpritePU()->getGlobalBounds()[1]/2);
    powerUps[2]->getSpritePU()->setScale(0.25, 0.3);
    powerUps[2]->getSpritePU()->setPosition(tamanyoX*(float)3/4 - 10, tamanyoY-tamanyoY*(float)4/7);


    //Este rectángulo se dibujará por detrás, y simulará un borde para el Sprite (para mostrar cuál está seleccionado)
    recSeleccion = new sf::RectangleShape(sf::Vector2f(powerUps[0]->getSpritePU()->getGlobalBounds()[0] + kMargen/2,
                                                       powerUps[0]->getSpritePU()->getGlobalBounds()[1] + kMargen/2));

    recSeleccion->setOrigin(recSeleccion->getGlobalBounds().width/2, recSeleccion->getGlobalBounds().height/2);
    recSeleccion->setFillColor(sf::Color(255, 230, 15));
    recSeleccion->setPosition(powerUps[0]->getSpritePU()->getPosition()[0], powerUps[0]->getSpritePU()->getPosition()[1]);


    configurarPrecios(precio1, powerUps[0]->getPrecio(), 0);
    configurarPrecios(precio2, powerUps[1]->getPrecio(), 1);
    configurarPrecios(precio3, powerUps[2]->getPrecio(), 2);


    dineroJugador = new sf::Text("Dinero total: " + std::to_string(dineroAhorrado), *fuente, 30);
    dineroJugador->setColor(sf::Color::White);
    dineroJugador->setPosition(tamanyoX - dineroJugador->getGlobalBounds().width, kMargen);


    //Información de los Power-Ups
    nombres = {powerUps[0]->getNombre(), powerUps[1]->getNombre(), powerUps[2]->getNombre()};
    descripciones = {powerUps[0]->getDescripcion(), powerUps[1]->getDescripcion(), powerUps[2]->getDescripcion()};

    //De momento no tienen string asociado
    configurarInfo(nom, 30, 80, 450);
    configurarInfo(descrip, 20, 90, 500);

    cajaDialogo = new Sprite(TexturaContainer::instancia()->getTextura("SpritesDialogos"));
    cajaDialogo->setRectTextura(sf::IntRect(0,128,800,250));
    cajaDialogo->setOrigin(cajaDialogo->getGlobalBounds()[0]/2,cajaDialogo->getGlobalBounds()[1]/2);
    cajaDialogo->setScale(0.9f, 0.6f);
    cajaDialogo->setPosition(800/2, 500);

}


void StateEnTienda::configurarPowerUps(sf::RectangleShape*& r, sf::Color color, float n1, float n2) {
    r = new sf::RectangleShape(sf::Vector2f(100.f, 150.f));
    r->setFillColor(sf::Color::White);
    r->setOutlineColor(color);
    r->setOutlineThickness(10.f);
    r->setOrigin(r->getGlobalBounds().width/2, r->getGlobalBounds().height/2);
    r->setPosition(tamanyoX*n1, tamanyoY - tamanyoY*n2);

    //powerUps.push_back(r);
}


void StateEnTienda::configurarPrecios(sf::Text*& precio, int num, int numPowerUp) {
    precio = new sf::Text(std::to_string(num), *fuente, 30);
    precio->setColor(sf::Color::White);
    precio->setOrigin(precio->getGlobalBounds().width/2, precio->getGlobalBounds().height/2);
    precio->setPosition(powerUps[numPowerUp]->getSpritePU()->getPosition()[0] - kMargen/2,
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
    //dtor
}
