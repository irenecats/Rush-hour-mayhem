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
    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::Return) {

        //Hay que comprobar que el jugador tenga dinero suficiente
        //toAnsiString() convierte sf::String a String y std::stoi convierte un string a int (activar [-std=c++11])
        if(dineroAhorrado >= std::stoi(precios[seleccionado]->getString().toAnsiString())) {
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

    if(seleccionado > (powerUps.size()-1))
        seleccionado = 0;


    for(int i=0; i<powerUps.size(); i++)
        powerUps[i]->setFillColor(sf::Color::White);

    powerUps[seleccionado]->setFillColor(sf::Color::Yellow);
    descrip->setString(descripciones[seleccionado]);
    nom->setString(nombres[seleccionado]);
}

void StateEnTienda::render(Window& window, const float updateTickTime)
{
    window.clear();

    window.draw(*titulo);
    window.draw(*r1);
    window.draw(*r2);
    window.draw(*r3);
    window.draw(*precio1);
    window.draw(*precio2);
    window.draw(*precio3);
    window.draw(*dineroJugador);
    window.draw(cajaDialogo->getSprite());
    window.draw(*nom);
    window.draw(*descrip);

    window.display();
}

StateEnTienda::StateEnTienda()
{
    id = ID_State::enTienda;

    fpu = new FactoryPowerUp();
    powerUp = fpu->crearPowerUp(1);
    powerUp2 = fpu->crearPowerUp(2);
    powerUp3 = fpu->crearPowerUp(3);

    fuente = new sf::Font();

    if (!fuente->loadFromFile("resources/JosefinSans-Regular.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    titulo = new sf::Text("Tiendecilla de Power-Ups", *fuente, 30);
    titulo->setColor(sf::Color::White);
    titulo->setPosition(kMargen, kMargen);


    std::string url ("resources/box.png");
    TexturaContainer::instancia()->crearTextura(url);
    cajaDialogo = new Sprite(TexturaContainer::instancia()->getTextura(4));
    cajaDialogo->setScale(0.2f, 0.15f);
    cajaDialogo->setPosition(kMargen, tamanyoY - cajaDialogo->getGlobalBounds()[1] - kMargen);


    configurarPowerUps(r1, sf::Color(255, 0, 0), (float)1/4, (float)4/7);
    configurarPowerUps(r2, sf::Color(255, 255, 0), (float)2/4, (float)4/7);
    configurarPowerUps(r3, sf::Color(255, 0, 255), (float)3/4, (float)4/7);

    configurarPrecios(precio1, powerUp->getPrecio(), 0);
    configurarPrecios(precio2, 300, 1);
    configurarPrecios(precio3, 1000, 2);


    dineroJugador = new sf::Text("Dinero total: " + std::to_string(dineroAhorrado) + "€", *fuente, 30);
    dineroJugador->setColor(sf::Color::White);
    dineroJugador->setPosition(tamanyoX - dineroJugador->getGlobalBounds().width, kMargen);


    //De momento no tienen string asociado
    configurarInfo(nom, 2.5, 0);
    configurarInfo(descrip, 2.5, 2);

    nombres = {powerUp->getNombre(), powerUp2->getNombre(), powerUp3->getNombre()};
    descripciones = {powerUp->getDescripcion(), powerUp2->getDescripcion(), powerUp3->getDescripcion()};
}


void StateEnTienda::configurarPowerUps(sf::RectangleShape*& r, sf::Color color, float n1, float n2) {
    r = new sf::RectangleShape(sf::Vector2f(100.f, 150.f));
    r->setFillColor(sf::Color::White);
    r->setOutlineColor(color);
    r->setOutlineThickness(10.f);
    r->setOrigin(r->getGlobalBounds().width/2, r->getGlobalBounds().height/2);
    r->setPosition(tamanyoX*n1, tamanyoY - tamanyoY*n2);

    powerUps.push_back(r);
}


void StateEnTienda::configurarPrecios(sf::Text*& precio, int num, int numPowerUp) {
    precio = new sf::Text(std::to_string(num), *fuente, 30);
    precio->setColor(sf::Color::White);
    precio->setOrigin(precio->getGlobalBounds().width/2, precio->getGlobalBounds().height/2);
    precio->setPosition(powerUps[numPowerUp]->getPosition().x - kMargen/2,
                       powerUps[numPowerUp]->getPosition().y - powerUps[numPowerUp]->getGlobalBounds().height/2 - kMargen*2);

    precios.push_back(precio);
}


void StateEnTienda::configurarInfo(sf::Text*& tex, float x, float y) {
    tex = new sf::Text(" ", *fuente, 30);
    tex->setColor(sf::Color::White);
    tex->setPosition(cajaDialogo->getPosition()[0] + kMargen*x, cajaDialogo->getPosition()[1] + kMargen*y);
}


StateEnTienda::~StateEnTienda()
{
    //dtor
}
