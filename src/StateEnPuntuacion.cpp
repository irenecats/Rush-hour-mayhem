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
    {
        if(StateEnJuego::instance()->getRuta() && !finjuego)
        {
            printf("Pantalla Final\n");
            finjuego = true;

            std::time_t t = std::time(0);   // get time now
            std::tm* now = std::localtime(&t);
            int day = now->tm_mday;
            int month = now->tm_mon + 1;
            int year = now->tm_year + 1900;
            int hour = now->tm_hour;
            int minute = now->tm_min;
            currentTime = std::to_string(day)+"/"+std::to_string(month)+"/"+std::to_string(year)+"\t"+
                          std::to_string(hour)+":"+std::to_string(minute);
            muestraFinal();
        }
        else if(StateEnJuego::instance()->getRuta() && finjuego)
        {
            next_state = ID_State::inicio;
        }
        else
        {
            limpiar();
            next_state = ID_State::enTienda;
        }
    }

    return next_state;
}

void StateEnPuntuacion::update(int tiempo)
{

    if(c <= col)
    {
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

    if(t <= tiemp)
    {
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
    if(t >= tiemp && c >= col && relleno->getSize().x <= rect->getSize().x * porcentaje / 100)
    {
        int incremento = 5;

        if(rect->getSize().x - relleno->getSize().x < 5)
            incremento = rect->getSize().x - relleno->getSize().x;

        relleno->setSize(sf::Vector2f(relleno->getSize().x + incremento, 30));
    }


    //Cuando ha terminado lo anterior, pasamos a mostrar el dinero total obtenido en la misión
    if(t >= tiemp && c >= col && relleno->getSize().x >= (rect->getSize().x * porcentaje/100) && d <= dinero)
    {
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
    window.draw(fondo);
    if(!finjuego)
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
    else
    {
        window.draw(titulo);
        window.draw(numeros);
        window.draw(fecha);
        window.draw(puntos);
        window.draw(oro);
        window.draw(plata);
        window.draw(bronce);
        window.draw(flecha);
    }
}

StateEnPuntuacion::StateEnPuntuacion()
{
    id = ID_State::enPuntuacion;

    fuente = new sf::Font();
    if (!fuente->loadFromFile("resources/Ticketing.ttf"))
    {
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

    titulo.setFont(*fuente);
    titulo.setString("Ranking de puntuaciones");
    titulo.setOrigin(titulo.getGlobalBounds().width/2,titulo.getGlobalBounds().height/2);
    titulo.setPosition(400,90);

    fecha.setFont(*fuente);
    fecha.setPosition(400,130);

    puntos.setFont(*fuente);
    puntos.setPosition(200,130);


    numeros.setFont(*fuente);
    numeros.setString("1.\n2.\n3.\n4.\n5.\n6.\n7.\n8.\n9.\n10.\n");
    numeros.setPosition(150,130);

    std::string urlIntro = "resources/photo_1.png";
    TexturaContainer::instancia()->crearTextura(urlIntro, "ciudad_fondo");
    fondo.setTextura(TexturaContainer::instancia()->getTextura("ciudad_fondo"));
    sf::Vector2f targetSize(800.0f, 600.0f);

    fondo.setScale(
        targetSize.x / fondo.getSprite().getLocalBounds().width,
        targetSize.y / fondo.getSprite().getLocalBounds().height);

    flecha.setTextura(TexturaContainer::instancia()->getTextura("Brujula"));
    flecha.setScale(0.02,0.02);
    flecha.setRotation(90);
    flecha.getSprite().setColor(sf::Color::White);

    urlIntro = "resources/medallas.png";
    TexturaContainer::instancia()->crearTextura(urlIntro, "monedas");

    oro.setTextura(TexturaContainer::instancia()->getTextura("monedas"));
    oro.setRectTextura(sf::IntRect(0,0,79,79));
    oro.setScale(0.35,0.35);
    oro.setPosition(90,136);

    plata.setTextura(TexturaContainer::instancia()->getTextura("monedas"));
    plata.setRectTextura(sf::IntRect(90,0,79,79));
    plata.setScale(0.35,0.35);
    plata.setPosition(90,171);

    bronce.setTextura(TexturaContainer::instancia()->getTextura("monedas"));
    bronce.setRectTextura(sf::IntRect(180,0,79,79));
    bronce.setScale(0.4,0.4);
    bronce.setPosition(90,207);

}


void StateEnPuntuacion::calcularPuntuacion (int colisiones, float tiempo, float tiempoPerfecto, float dineroPerfecto)
{
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


void StateEnPuntuacion::crearText(sf::Text*& text, std::string str, int tamanyo, float x, float y)
{
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
    porcentaje = 0.f;
    dinero = 0.f;

    col = 15;
    tiemp = 80;
    tiempoPerf = 60;
    dineroPerf = 350;

    c = 0;
    t = 0;
    d = 0;

    calcularPuntuacion(col, tiemp, tiempoPerf, dineroPerf);

    ncoli->setString(std::to_string(c));
    ntiemp->setString(std::to_string(t));
    ndinero->setString(std::to_string(d));

    if(rect)
        delete rect;
    if(relleno)
        delete relleno;

    rect = new sf::RectangleShape(sf::Vector2f(310,40));
    rect->setOrigin(rect->getGlobalBounds().width/2, rect->getGlobalBounds().height/2);
    rect->setPosition(800/2, 350);
    rect->setOutlineColor(sf::Color::White);

    relleno = new sf::RectangleShape(sf::Vector2f(0, 30));
    relleno->setOrigin(relleno->getGlobalBounds().width/2, relleno->getGlobalBounds().height/2);
    relleno->setPosition(rect->getPosition().x - rect->getGlobalBounds().width/2 + 5, rect->getPosition().y);
    relleno->setFillColor(sf::Color::Green);
}

void StateEnPuntuacion::muestraFinal()
{
    leeFichero();
    organizaRanking();
}

void StateEnPuntuacion::organizaRanking()
{
    std::string fechaux;
    std::string puntosaux;

    for(unsigned int i=0; i<10 ; i++)
    {
        if(i<rango.size())
        {
            fechaux += rango[i][0]+"\n";
            puntosaux += rango[i][1]+"\n";
        }
        else
        {
            fechaux+="\t---\n";
            puntosaux +="\t---\n";
        }
    }

    if(currentPos>10)
    {
        std::string num = numeros.getString();
        fechaux += "\n"+currentTime;
        puntosaux += "\n"+std::to_string(Jugador::instancia()->getDineroTotal());
        num += "\n"+std::to_string(currentPos)+".";
        numeros.setString(num);
    }

    fecha.setString(fechaux);
    if(currentPos<=10){
        flecha.setPosition(700,150+35*(currentPos - 1));
    }
    else{
        flecha.setPosition(700,521);
    }
    puntos.setString(puntosaux);
}

void StateEnPuntuacion::leeFichero()
{
    std::vector <std::string> frases;
    std::ifstream fichero("resources/ranking.txt");
    bool introducido = false;

    for(std::string linea; getline(fichero,linea);)
    {
        char separador  = '#';

        //Si la línea contiene un ;
        if(linea.find(separador) != std::string::npos)
        {

            //Nos guardamos esa línea y pasaremos a trabajar sobre ella
            std::stringstream miniFichero(linea);
            std::vector <std::string> fila ;
            std::string trozoLinea;
            std::string nuevaLinea;
            //Parseamos nuestra línea en sublíneas separadas por #
            while (std::getline(miniFichero, trozoLinea, separador))
            {
                fila.push_back(trozoLinea);
            }
            int lista = std::stoi(fila[1]);

            if (lista < Jugador::instancia()->getDineroTotal() && !introducido)
            {
                introducido = true;
                std::vector<std::string> usuario {currentTime,std::to_string(Jugador::instancia()->getDineroTotal())};
                rango.push_back(usuario);
                currentPos = rango.size();
                std::cout<<currentPos<<std::endl;
            }
            rango.push_back(fila);
        }
    }
    if(!introducido)
    {
        introducido = true;
        std::vector<std::string> usuario {currentTime,std::to_string(Jugador::instancia()->getDineroTotal())};
        rango.push_back(usuario);
        currentPos = rango.size();

    }

    fichero.close();
    std::ofstream mifichero;
    mifichero.open("resources/ranking.txt");

    for(unsigned int i=0; i<rango.size(); i++)
    {
        mifichero << rango[i][0]+"#"+rango[i][1]+"\n";
    }
    mifichero.close();
}
