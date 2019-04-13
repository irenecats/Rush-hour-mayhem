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
    int dinero = 0;
    const char* fichero;
    std::string personaje = "";
    sf::IntRect areaRecorte;

    switch(numRuta){
        case 1:
            inicio.x = 10.0;
            inicio.y = 10.0;
            fin.x = 100.0;
            fin.y = 100.0;
            dinero = 300;
            fichero = "resources/pija.txt";
            personaje   = "Brittany";  //o tiffany, se aceptan propuestas
            areaRecorte = sf::IntRect(0,0,128,128);
            break;

        case 2:
            areaRecorte = sf::IntRect(128,0,128,128);
            break;

        case 3:
            areaRecorte = sf::IntRect(256,0,128,128);
            break;

        case 4:
            areaRecorte = sf::IntRect(384,0,128,128);
            break;

        case 5:
            areaRecorte = sf::IntRect(512,0,128,128);
            break;
    }

    return new Ruta(numRuta, inicio, fin, false, dinero, fichero, personaje, areaRecorte);
}
