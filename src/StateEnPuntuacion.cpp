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
    next_state = id;

    if(teclaPulsada == sf::Keyboard::Return)
        next_state = ID_State::enTienda;

    return next_state;
}

void StateEnPuntuacion::update()
{

     if(c <= col) {
        ncoli->setString(std::to_string(c));
        ncoli->setOrigin(ncoli->getGlobalBounds().width/2, ncoli->getGlobalBounds().height/2);
        ncoli->setPosition(800/3, 200);

        //Incrementamos el valor para la siguiente iteración
        if(col-c >= 5)
            c+=5;
        else if(col-c == 0) //para que no esté haciéndolo en bucle
            c=col+1;
        else
            c=col-c;
    }

    if(t <= tiemp) {
        ntiemp->setString(std::to_string(t));
        ntiemp->setOrigin(ntiemp->getGlobalBounds().width/2, ntiemp->getGlobalBounds().height/2);
        ntiemp->setPosition(800-800/3, 200);

        if(tiemp-t >= 5)
            t+=5;
        else if(tiemp-t == 0)
            t=tiemp+1;
        else
            t = tiemp-t;
    }

    //Cuando ya han terminado de aparecer los resultados anteriores, se muestra la barra de porcentaje
    //Se crea lo "verde" hasta que su ancho es igual que el de la barra blanca multiplicada por el porcentaje
    if(t >= tiemp && c >= col && relleno->getSize().x <= rect->getSize().x * porcentaje / 100) {
        int incremento = 5;

        if(rect->getSize().x - relleno->getSize().x < 5)
            incremento = rect->getSize().x - relleno->getSize().x;

        relleno->setSize(sf::Vector2f(relleno->getSize().x + incremento, 30));
    }


    //Cuando ha terminado lo anterior, pasamos a mostrar el dinero total obtenido en la misión
    if(t >= tiemp && c >= col && relleno->getSize().x >= (rect->getSize().x * porcentaje/100) && d <= dinero) {
        ndinero->setString(std::to_string(d));

        //Todo el rato se actualiza el origen pq si el número pasa de 1 a 2, 3... las cifras se descentran
        ndinero->setOrigin(ndinero->getGlobalBounds().width/2, ndinero->getGlobalBounds().height/2);
        ndinero->setPosition(575, 495);

        //También sacamos el "label" asociado a la cantidad del dinero
        dineroObtenido->setString("Dinero obtenido: ");
        dineroObtenido->setOrigin(dineroObtenido->getGlobalBounds().width/2, dineroObtenido->getGlobalBounds().height/2);
        dineroObtenido->setPosition(330, 500);

        if(dinero-d >= 5)
            d+=5;
        else if(dinero-d == 0)
            d=dinero+1;
        else
            d = dinero-d;
    }
}

void StateEnPuntuacion::render(Window &window, const float updateTickTime)
{
    window.draw(*resultados);
    window.draw(*colisiones);
    window.draw(*tiempo);
    window.draw(*ncoli);
    window.draw(*ntiemp);
    window.draw(*ndinero);
    window.draw(*dineroObtenido);
    window.draw(*rect);
    window.draw(*relleno);
}

StateEnPuntuacion::StateEnPuntuacion()
{
    id = ID_State::enPuntuacion;

    fuente = new sf::Font();
    if (!fuente->loadFromFile("resources/Ticketing.ttf")) {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }

    calcularPuntuacion(col, tiemp, tiempoPerf, dineroPerf);

    crearText(resultados, "RESULTADOS DE LA MISION", 50, 800/2, 50);
    crearText(colisiones, "Colisiones", 30, 800/3, 150);
    crearText(tiempo, "Tiempo", 30, 800-800/3, 150);

    //Valores básicos, en el update se cambiarán
    crearText(ncoli, " ", 75, 0, 0);
    crearText(ntiemp, " ", 75, 0, 0);
    crearText(ndinero, " ", 75, 0, 0);
    crearText(dineroObtenido, " ", 50, 0, 0);

    //Para la barra de porcentaje
    rect = new sf::RectangleShape(sf::Vector2f(310,40));
    rect->setOrigin(rect->getGlobalBounds().width/2, rect->getGlobalBounds().height/2);
    rect->setPosition(800/2, 350);
    rect->setOutlineColor(sf::Color::White);

    relleno = new sf::RectangleShape(sf::Vector2f(0, 30));
    relleno->setOrigin(relleno->getGlobalBounds().width/2, relleno->getGlobalBounds().height/2);
    relleno->setPosition(rect->getPosition().x - rect->getGlobalBounds().width/2 + 5, rect->getPosition().y);
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
    dinero *= (float)tiempoPerfecto/tiempo;
    dinero = (int)dinero;

    porcentaje = dinero / dineroPerfecto * 100.f;

    //Actualizamos las variables de dinero del jugador
    Jugador::instancia()->setDinero(dinero);
}


void StateEnPuntuacion::crearText(sf::Text*& text, std::string str, int tamanyo, float x, float y) {
    text = new sf::Text(str, *fuente, tamanyo);
    text->setColor(sf::Color::White);
    text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
    text->setPosition(x, y);
}


StateEnPuntuacion::~StateEnPuntuacion()
{
    delete resultados;
    delete colisiones;
    delete tiempo;
    delete ncoli;
    delete ndinero;
    delete dineroObtenido;
    delete rect;
    delete relleno;
    delete fuente;
}

void StateEnPuntuacion::inicializar()
{

}

void StateEnPuntuacion::limpiar()
{

}
