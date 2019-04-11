#include "Ruta.h"

Ruta::Ruta()
{
    //ctor
}

Ruta::~Ruta()
{
    //
    delete destino;
    delete origen;
}

Ruta::Ruta(sf::Vector2f inicio, sf::Vector2f fin, bool client, int dinero, char* titulo,std::string name, std::string urlCliente)
{
    //ctor
    sf::Vector2f tam(10.0,10.0);
    //inicializamos valores generales de ruta
    activa      = false;
    origen      = new sf::RectangleShape(tam);
    destino     = new sf::RectangleShape(tam);
    dineroMax   = dinero;


    //cargamos la textura en el texture manager y lo metemos
    std::string urlIntro="resources/box.png";
    int numtext1 = TexturaContainer::instancia()->crearTextura(urlCliente);

    tex = TexturaContainer::instancia()->crearTextura(urlIntro);


    //cliente.setTextura(TexturaContainer::instancia()->getTextura(numtext1));
    //me tendrán que devolver algo y yo me lo guardo
    //hay que cambia
    cliente.setTextura(TexturaContainer::instancia()->getTextura(0));
    cajaDialogo.setTextura(TexturaContainer::instancia()->getTextura(tex));

    //ponemos el origen el en centro y posicionamos el inicio y el fin de la ruta
    origen->setOrigin(origen->getSize().x/2,origen->getSize().y/2);
    origen->setPosition(inicio);
    origen->setFillColor(sf::Color::Red);

    destino->setOrigin(destino->getSize().x/2,destino->getSize().y/2);
    destino->setPosition(fin);
    destino->setFillColor(sf::Color::Blue);

    //leemos el fichero y guardamos
    leefichero(titulo);

    //cargamos y seteamos lo necesario para mostrar los dialogos

    if (!fuente.loadFromFile("resources/Ticketing.ttf"))
    {
        std::cerr << "Error al cargar la fuente\n" << std::endl;
        exit(0);
    }
    dialogo.setFont(fuente);
    dialogo.setColor(sf::Color::White);

    nombre.setColor(sf::Color::White);
    nombre.setFont(fuente);
    nombre.setString(name);

    cajaDialogo.setOrigin(cajaDialogo.getGlobalBounds()[0],cajaDialogo.getGlobalBounds()[1]/2);

    DiagActual  = 0;
    letra       = 0;
    numfrase    = 0;
}
/*
    Lee el fichero asignado y guarda los dialgos en las variables de clase "dialogointro" y
    "dialogochoque".
    El salto de linea se indica con ";" y los dos tipos de dialogo se separaran con "&".
*/
void Ruta::leefichero(char* titulo)
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
            cambio=true;
            std::string trozoLinea;
            linea=linea.substr(1,linea.size());
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
    //delete titulo;
}

void Ruta::haLlegado()
{
    printf("preparo\n");
    activa = true;
    setDiagActual(1);

}

void Ruta::cambiaEstiloDialogo()
{

    switch(DiagActual)
    {
    case 1:
        //preparo el dialogo
        nombre.setCharacterSize(30);
        nombre.setPosition(80, 450);

        dialogo.setCharacterSize(20);
        dialogo.setPosition(90, 500);

        cajaDialogo.setScale(0.9f, 0.6f);
        cajaDialogo.setPosition(760, 500);


        break;
    case 2:
        //  TODO determinar estilo, por ahora solo cambiaremos el color

        nombre.setCharacterSize(20);
        nombre.setPosition(180, 460);

        dialogo.setCharacterSize(30);
        dialogo.setPosition(190, 500);

        cajaDialogo.setScale(0.5f, 0.5f);
        cajaDialogo.setPosition(550, 500);
        break;
    default:
        break;
    }
}

void Ruta::Update(Clock& tiempo)
{
    if(activa && DiagActual==1 && numfrase < dialogointro.size() )
    {
        //printf("%f",tiempo.getElapsedTime());
        if (tiempo.getElapsedTime()> 50 && letra < dialogointro[numfrase].length())
        {
            //frases[numfrase].length()
            tiempo.restart();
            letra++;
            //Mostramos por pantalla un substring de la frase. Con cada iteración aumenta el substring, consiguiendo el efecto de aparición
            //de las letras poco a poco.
            dialogo.setString(dialogointro[numfrase].substr(0, letra));

        }
        else if (letra >= dialogochoque[numfrase].length())
        {
            dialogo.setString(dialogointro[numfrase]);
        }
    }
    else if(activa && DiagActual == 2)
    {
        //dialogo.setString(dialogochoque[numfrase]);
        if(tiempo.getElapsedTime() >= 2000)
        {
            tiempo.restart();
            DiagActual = 0;

        }
        printf("%i\n",numfrase);
    }
}

void Ruta::Render(Window& window)
{
    if(!activa)
    {
        window.draw(*origen);
    }
    else
    {
        if(DiagActual!=0)
        {
            window.draw(cajaDialogo.getSprite());
            window.draw(dialogo);
            window.draw(nombre);
        }
        window.draw(*destino);
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
    if(tipo==2){
        numfrase = rand() % dialogochoque.size();
        dialogo.setString(dialogochoque[numfrase]);
    }
    cambiaEstiloDialogo();
}

void Ruta::pasarDialogo()
{

    if(numfrase < dialogointro.size()-1 && DiagActual==1)
    {
        numfrase++;
    }
    else
    {
        //numfrase=0;
        setDiagActual(0);
    }
    printf("Numeo de frase: %i \n",numfrase);
}