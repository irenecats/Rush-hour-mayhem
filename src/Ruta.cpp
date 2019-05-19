#include "Ruta.h"

Ruta::Ruta() {}

Ruta::~Ruta()
{
    delete destino;
    delete origen;
}

Ruta::Ruta(int id, sf::Vector2f inicio, sf::Vector2f fin, bool client, int dinero, const char* titulo,std::string name, sf::IntRect areaRecorte, std::vector<sf::Vector2f> g)
{

    //Inicializamos valores generales de ruta
    idRuta = id;
    nombreCliente = name;
    sf::Vector2f tam(50.0,50.0);
    activa      = false;
    terminada   = false;
    origen      = new sf::RectangleShape(tam);
    destino     = new sf::RectangleShape(tam);

    //Ponemos el origen el en centro y posicionamos el inicio y el fin de la ruta
    origen->setOrigin(origen->getSize().x/2,origen->getSize().y/2);
    origen->setPosition(inicio);
    origen->setFillColor(sf::Color::Red);

    destino->setOrigin(destino->getSize().x/2,destino->getSize().y/2);
    destino->setPosition(fin);
    destino->setFillColor(sf::Color::Blue);

    //Solo carga el spritesheet de los personajes cuando se crea la primera ruta
    if(idRuta == 1) {
        std::string urlIntro = "resources/personajesDialogo.png";
        TexturaContainer::instancia()->crearTextura(urlIntro, "SpritesDialogos");
    }

    cliente.setTextura(TexturaContainer::instancia()->getTextura("SpritesDialogos"));
    cliente.setRectTextura(areaRecorte);

    cajaDialogo.setTextura(TexturaContainer::instancia()->getTextura("SpritesDialogos"));
    cajaDialogo.setRectTextura(sf::IntRect(0,128,800,250));
    cajaDialogo.setOrigin(cajaDialogo.getGlobalBounds()[0]/2,cajaDialogo.getGlobalBounds()[1]/2);



    //Leemos el fichero y guardamos
    leefichero(titulo);

    //Cargamos y seteamos lo necesario para mostrar los dialogos
    if (!fuente.loadFromFile("resources/Ticketing.ttf"))
    {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }
    //Ponemos estilo a los cuadros de dialogo
    //Solo serán los atributos comunes entre el diag de inicio y el de choque
    dialogo.setFont(fuente);
    dialogo.setColor(sf::Color::White);

    nombre.setColor(sf::Color::White);
    nombre.setFont(fuente);
    nombre.setString(nombreCliente);

    DiagActual  = 0;
    letra       = 0;
    numfrase    = 0;
    guia = g;

}


/*
    Lee el fichero asignado y guarda los dialgos en las variables de clase "dialogointro" y "dialogochoque".
    El salto de linea se indica con ";" y los dos tipos de dialogo se separaran con "&".
*/
void Ruta::leefichero(const char* titulo)
{

    std::vector <std::string> frases;
    std::vector <std::string> quejas;
    std::ifstream fichero(titulo);

    bool cambio = false;
    for(std::string linea; getline(fichero,linea);)
    {

        char separador  = ';';
        char separador2 = '&';

        //Si la línea contiene un ;
        if(linea.find(separador) != std::string::npos)
        {

            //Nos guardamos esa línea y pasaremos a trabajar sobre ella
            std::stringstream miniFichero(linea);
            std::string trozoLinea;
            std::string nuevaLinea;

            //Parseamos nuestra línea en sublíneas separadas por ;
            while (std::getline(miniFichero, trozoLinea, separador))
            {
                //Le metemos un salto de línea entre estas sublíneas.
                nuevaLinea = nuevaLinea + trozoLinea + "\n";
            }

            linea = nuevaLinea;
        }
        if(linea.find(separador2) != std::string::npos)
        {
            //Todas las siguientes lineas se almacenan en quejas
            //Le quitamos el separador2 "&" a la primera queja
            cambio = true;
            std::string trozoLinea;
            linea = linea.substr(1,linea.size());
        }

        //Añadimos la línea a nuestro vector de frases
        if(cambio)
        {
            quejas.push_back(linea);
        }
        else
        {
            frases.push_back(linea);
        }
    }

    fichero.close();

    dialogointro  = frases;
    dialogochoque = quejas;
}

/*
    Activa la ruta y llama al método que realiza el cambio de estilo del cuadro de dialogo
*/
void Ruta::haLlegado()
{
    printf("preparo\n");
    activa = true;
    setDiagActual(1);

}

void Ruta::haTerminado(){
    terminada = true;
}

/*
    Dependiendo del tipo del dialogo actual anyadimos un estilo u otro
    a los cuadros de dialogo
*/
void Ruta::cambiaEstiloDialogo()
{
    switch(DiagActual)
    {
    case 1:
        nombre.setCharacterSize(30);
        nombre.setPosition(80, 450);

        dialogo.setCharacterSize(20);
        dialogo.setPosition(90, 500);

        cajaDialogo.setScale(0.9f, 0.6f);
        cajaDialogo.setPosition(800/2, 500);

        cliente.setPosition(cajaDialogo.getPosition()[0] - cajaDialogo.getGlobalBounds()[0]/2 +5,
                            cajaDialogo.getPosition()[1] - cajaDialogo.getGlobalBounds()[1]/2 - cliente.getGlobalBounds()[1]);

        break;
    case 2:

        nombre.setCharacterSize(20);
        nombre.setPosition(220, 460);

        dialogo.setCharacterSize(30);
        dialogo.setPosition(220, 500);

        cajaDialogo.setScale(0.5f, 0.5f);
        cajaDialogo.setPosition(800/2, 500);
        break;
    default:
        break;
    }
}
/*
    Cambia a la siguiente frase, si ya se han acabado cambiamos DiagActual indicando que
    no hay ningun dialogo que mostrar en este momento
*/
void Ruta::pasarDialogo()
{

    if(numfrase < (int) dialogointro.size()-1 && DiagActual == 1)
    {
        letra = 0;
        numfrase++;
    }
    else
    {
        setDiagActual(0);
    }
    printf("Numero de frase: %i \n",numfrase);
}
/*
    Calcula como pasan los dialogos y cuanto tiempo duran en la pantalla dependiendo de su tipo
        Si Introduccion:
            Se escriben progresivamente y se cambia de oracion al pulsar el espacio
        Si Choque:
            Se muestran directamente y dejan de dibujarse tras 1 sefundo
*/
void Ruta::Update(Clock& tiempo)
{
    if(activa && DiagActual==1 && numfrase < (int) dialogointro.size() )
    {
        if (tiempo.getElapsedTime()> 25 && letra < (int) dialogointro[numfrase].length())
        {
            tiempo.restart();
            letra++;
            //Mostramos por pantalla un substring de la frase. Con cada iteración aumenta el substring, consiguiendo el efecto de aparición
            //de las letras poco a poco.
            dialogo.setString(dialogointro[numfrase].substr(0, letra));

            if(dialogointro[numfrase].at(0) == '(') {
                cliente.setTextura(nullptr);
                nombre.setString("");
            } else {
                cliente.setTextura(TexturaContainer::instancia()->getTextura("SpritesDialogos"));
                nombre.setString(nombreCliente);
            }


        }
        else if (letra >= (int) dialogochoque[numfrase].length())
        {
            dialogo.setString(dialogointro[numfrase]);
        }
    }
    else if(activa && DiagActual == 2)
    {
        if(tiempo.getElapsedTime() >= 1000)
        {
            tiempo.restart();
            DiagActual = 0;

        }
        printf("%i\n",numfrase);
    }
}
/*
    Dependiendo del estado de la ruta ,activa o inactiva, se mostrara el punto de inicio de la ruta o el final
*/
void Ruta::RenderPuntos(Window& window)
{
    if(!activa)
    {
        window.draw(*origen);
    }
    else
    {
        window.draw(*destino);
    }
}

/*
    Se encuentra separado del anterior Render debido a que se tiene que dibujar sobre otra view
    Dibuja el cuadro de dialogo con el fondo, nombre y frase del cliente, si estamos en la
    introduccion, tambien dibujaremos el sprite del cliente
*/
void Ruta::RenderDialogos(Window& window)
{
        if(DiagActual!=0)
        {
            window.draw(cajaDialogo);
            window.draw(dialogo);
            window.draw(nombre);

            if(DiagActual == 1)
                window.draw(cliente);
        }
}


sf::RectangleShape* Ruta::getOrigen()
{
    return origen;
}

sf::RectangleShape* Ruta::getDestino()
{
    return destino;
}

bool Ruta::getActiva()
{
    return activa;
}

int Ruta::getDiagActual()
{
    return DiagActual;
}

void Ruta::setDiagActual(int tipo)
{
    printf("Tipo : %i",tipo);
    DiagActual = tipo;
    if(tipo == 2){
        numfrase = rand() % dialogochoque.size();
        dialogo.setString(dialogochoque[numfrase]);
    }
    cambiaEstiloDialogo();
}

bool Ruta::getTerminada(){
    return terminada;
}

int Ruta::getID(){
    return idRuta;
}

std::vector<sf::Vector2f> Ruta::getGuia(){
    return guia;
}
