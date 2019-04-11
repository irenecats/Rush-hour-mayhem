#include "StateEnPuntuacion.h"

StateEnPuntuacion* StateEnPuntuacion::instancia = nullptr;

StateEnPuntuacion* StateEnPuntuacion::instance()
{
    if(!instancia)
        instancia = new StateEnPuntuacion;

    return instancia;
}

ID_State StateEnPuntuacion::input(int teclaPulsada)
{
    ID_State next_state = id;

    if(teclaPulsada == sf::Keyboard::T)
        next_state = ID_State::enTienda;

    return next_state;
}

void StateEnPuntuacion::update()
{

     if(c <= col) {
        ncoli->setString(std::to_string(c));
        ncoli->setOrigin(ncoli->getGlobalBounds().width/2, ncoli->getGlobalBounds().height/2);
        ncoli->setPosition(200, 200);

        c++; //Incrementamos el valor para la siguiente iteración
    }

    if(t <= tiemp) {
        ntiemp->setString(std::to_string(t));
        ntiemp->setOrigin(ntiemp->getGlobalBounds().width/2, ntiemp->getGlobalBounds().height/2);
        ntiemp->setPosition(440, 200);

        t++;
    }


    //Cuando ya han terminado de aparecer los resultados anteriores, se muestra la barra de porcentaje
    //Se crea lo "verde" hasta que su ancho es igual que el de la barra blanca multiplicada por el porcentaje
    if(t > tiemp && c > col && relleno->getSize().x <= rect->getSize().x * porcentaje / 100) {
        relleno->setSize(sf::Vector2f(relleno->getSize().x + 1, 40));
    }


    //Cuando ha terminado lo anterior, pasamos a mostrar el dinero total obtenido en la misión
    if(t > tiemp && c > col && relleno->getSize().x > rect->getSize().x * porcentaje / 100 && d <= dinero) {
        ndinero->setString(std::to_string(d));

        //Todo el rato se actualiza el origen pq si el número pasa de 1 a 2, 3... las cifras se descentran
        ndinero->setOrigin(ndinero->getGlobalBounds().width/2, ndinero->getGlobalBounds().height/2);
        ndinero->setPosition(500, 395);

        //También sacamos el "label" asociado a la cantidad del dinero
        dineroObtenido->setString("Dinero obtenido");
        dineroObtenido->setOrigin(dineroObtenido->getGlobalBounds().width/2, dineroObtenido->getGlobalBounds().height/2);
        dineroObtenido->setPosition(230, 400);

        d++;
    }
}

void StateEnPuntuacion::render(Window &window, const float updateTickTime)
{
    window.clear();

    window.draw(*resultados);
    window.draw(*colisiones);
    window.draw(*tiempo);
    window.draw(*ncoli);
    window.draw(*ntiemp);
    window.draw(*ndinero);
    window.draw(*dineroObtenido);
    window.draw(*rect);
    window.draw(*relleno);

    window.display();
}

StateEnPuntuacion::StateEnPuntuacion()
{
    id = ID_State::enPuntuacion;

    fuente = new sf::Font();
    if (!fuente->loadFromFile("resources/JosefinSans-Regular.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    calcularPuntuacion(col, tiemp, tiempoPerf, dineroPerf);

    crearText(resultados, "~ RESULTADOS ~", 50, 320, 50);
    crearText(colisiones, "N colisiones", 30, 200, 150);
    crearText(tiempo, "Tiempo", 30, 440, 150);


    //Valores básicos, en el update se cambiarán
    crearText(ncoli, " ", 75, 0, 0);
    crearText(ntiemp, " ", 75, 0, 0);
    crearText(ndinero, " ", 75, 0, 0);
    crearText(dineroObtenido, " ", 50, 0, 0);


    //Para la barra de porcentaje
    rect = new sf::RectangleShape();
    rect->setSize(sf::Vector2f(310, 40));
    rect->setPosition(175, 300);
    rect->setOutlineColor(sf::Color::White);

    relleno = new sf::RectangleShape();
    relleno->setSize(sf::Vector2f(0, 40));
    relleno->setPosition(rect->getPosition());
    relleno->setFillColor(sf::Color::Green);
}


void StateEnPuntuacion::calcularPuntuacion (int colisiones, float tiempo, float tiempoPerfecto, float dineroPerfecto) {


    //Se empieza teniendo todo el dinero, y de ahí se le va quitando.
    dinero = dineroPerfecto;

    //Las colisiones no quitan tanto pq va a haber MUCHAS
    for(int i = 0; i < colisiones; i++)
        dinero *= 0.99;


    //Por si lo hiciera más rápido (no va a pasar pero porsi)
    if (tiempo < tiempoPerfecto)
        tiempo = tiempoPerfecto;


    //Quitamos más cantidad de dinero si tarda mucho
    dinero *= tiempoPerfecto/tiempo;

    porcentaje = dinero / dineroPerfecto * 100.f;
}


void StateEnPuntuacion::crearText(sf::Text*& text, std::string str, int tamanyo, float x, float y) {
    text = new sf::Text(str, *fuente, tamanyo);
    text->setColor(sf::Color::White);
    text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
    text->setPosition(x, y);
}


StateEnPuntuacion::~StateEnPuntuacion()
{
    //dtor
}
