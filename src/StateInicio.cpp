#include "StateInicio.h"

StateInicio* StateInicio::instancia = nullptr;

StateInicio* StateInicio::instance()
{
    if(!instancia)
        instancia = new StateInicio;

    return instancia;
}

ID_State StateInicio::input(int teclaPulsada)
{
    /*
        teclaPulsada es el input de la ventana
        en principio, en el estado de inicio,
        este sera el unico tipo de input.

        Se podria implementar el raton, pasando
        por parametro una struct que habria que
        definir, desde Juego->StateManager->
        ->State->StateInicio, lo necesario para
        controlar el funcionamiento del raton
        (posicion del cursor, click, etc).
    */

    next_state = id;

    if(teclaPulsada == sf::Keyboard::Up)
    {
        if(seleccion == 0)
            seleccion = (int) opciones->size() - 1;
        else
            seleccion--;
    }

    if(teclaPulsada == sf::Keyboard::Down)
    {
        if(seleccion >= (int) opciones->size() - 1)
            seleccion = 0;
        else
            seleccion++;
    }

    if(teclaPulsada == sf::Keyboard::Return && !eninstrucciones){
        if(seleccion == 0){
            next_state = ID_State::enJuego;
        }
        else if(seleccion == 1){
            //cosas de mateo
        }
        else if(seleccion == 2){
           eninstrucciones = true;
        }
    }
    else if(teclaPulsada == sf::Keyboard::Return && eninstrucciones){
        eninstrucciones = false;
    }

    return next_state;
}

void StateInicio::update(int tiempo)
{
        for(int i = 0; i < (int) opciones->size(); ++i)
            if(seleccion == i)
                opciones->at(i)->setColor(sf::Color::White);
            else
                opciones->at(i)->setColor(sf::Color(128, 128, 128, 255));
}


void StateInicio::render(Window &window, const float updateTickTime)
{

    window.draw(*contenedorMenu);

    if(!eninstrucciones){
        for(sf::Text* &opcion : *opciones)
            window.draw(*opcion);
    }
    else{
        window.draw(textoinstrucciones);
    }
     window.draw(logo);
}

StateInicio::StateInicio()
{
    id = ID_State::inicio;
    //cargar imagen
}

StateInicio::~StateInicio()
{
    //dtor
}

void StateInicio::inicializar()
{
    fuente = new sf::Font();
    eninstrucciones = false;

    if (!fuente->loadFromFile("resources/Ticketing.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(-1);
    }

    nuevaPartida = new sf::Text(sf::String("Nueva Partida"), *fuente);
    cargarPartida = new sf::Text(sf::String("Cargar Partida"), *fuente);
    instrucciones = new sf::Text(sf::String("Instrucciones"), *fuente);

    contenedorMenu = new sf::RectangleShape(sf::Vector2f(800.f*0.8f, 600.f*0.8f));

    contenedorMenu->setOrigin(contenedorMenu->getSize().x / 2.f, 0);
    contenedorMenu->setPosition(800.f/2.f, 600.f*0.1f);
    contenedorMenu->setFillColor(sf::Color::Black);
    contenedorMenu->setOutlineThickness(4.f);
    contenedorMenu->setOutlineColor(sf::Color::Yellow);

    opciones = new std::vector<sf::Text*>();

    opciones->push_back(nuevaPartida);
    opciones->push_back(cargarPartida);
    opciones->push_back(instrucciones);

    for(int i = 0; i < (int) opciones->size(); ++i)
    {
        opciones->at(i)->setOrigin(opciones->at(i)->getGlobalBounds().width / 2.f, 0);
        opciones->at(i)->setPosition(contenedorMenu->getPosition().x, 140.f + (100.f * (i+1)));
    }

    std::string urlIntro = "resources/rush_hour_mayhem_texto.png";
    TexturaContainer::instancia()->crearTextura(urlIntro, "ciudad_fondo");
    logo.setTextura(TexturaContainer::instancia()->getTextura("ciudad_fondo"));
    logo.setOrigin(logo.getGlobalBounds()[0]/2,logo.getGlobalBounds()[1]/2);
    logo.setPosition(400,110);
    logo.setScale(0.5,0.5);

    textoinstrucciones.setFont(*fuente);
    textoinstrucciones.setScale(0.7,0.7);
    textoinstrucciones.setString("Hola estas son las instrucciones. Actualmente en desarrollo.");
    textoinstrucciones.setPosition(100,190);
;}

void StateInicio::limpiar()
{

}

