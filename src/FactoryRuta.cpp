#include "FactoryRuta.h"
#include <Ruta.h>
#include <Sprite.h>
#include <string>

FactoryRuta::FactoryRuta()
{
    //ctor
}

FactoryRuta::~FactoryRuta()
{
    //dtor
}

Ruta* FactoryRuta::creaRuta(int numRuta){

 sf::Vector2f inicio(0.0,0.0);
 sf::Vector2f fin(0.0,0.0);
// Sprite client = NULL;
 int dinero = 0;
 char* titulo = "";
 std::string name = "" ;
 std::string urlCliente = "";
 //Sprite sprite;

    switch(numRuta){
        case 1:
            inicio.x=10.0;
            inicio.y=10.0;
            fin.x =40.0;
            fin.y=40.0;
            dinero = 300;
            titulo = "resources/pepi.txt";
            name   = "Pepi";
            urlCliente = "resources/Pam.png";
            //sprite.setTextura();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;

    }


    return new Ruta(inicio, fin, false, dinero, titulo, name, urlCliente);
}
