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
    std::vector<sf::Vector2f> guia;

    switch(numRuta){
        case 1:
<<<<<<< Updated upstream

            inicio.x = 405*32;
            inicio.y = 288*32;
=======
>>>>>>> Stashed changes

            //inicio.x = 405*32;
            //inicio.y = 288*32;

            inicio.x = 250*32;
            inicio.y = 360*32;
            //fin.x = 226*32;
            //fin.y = 349*32;
            fin.x = 240*32;
            fin.y = 360*32;
            dinero = 300;
            fichero = "resources/pija.txt";
            personaje   = "Brittany";  //o tiffany, se aceptan propuestas
            areaRecorte = sf::IntRect(0,0,128,128);
            guia.push_back(sf::Vector2f(250*32,360*32));
            guia.push_back(sf::Vector2f(260*32,360*32));
            guia.push_back(sf::Vector2f(260*32,370*32));
            guia.push_back(sf::Vector2f(270*32,370*32));
            break;

        case 2:
<<<<<<< Updated upstream

            inicio.x = 8000.0;
            inicio.y = 10000.0;
            fin.x = 7232.0;
            fin.y = 11072.0;
=======
            //inicio.x = 7000.0;
            //inicio.y = 10000.0;
            //fin.x = 240*32;
            //fin.y = 360*32;
            inicio.x = 250*32;
            inicio.y = 360*32;
            //fin.x = 226*32;
            //fin.y = 349*32;
            fin.x = 240*32;
            fin.y = 360*32;
>>>>>>> Stashed changes
            fichero = "resources/embarazada.txt";
            personaje   = "Embarazada";
            areaRecorte = sf::IntRect(128,0,124,128);
            break;

        case 3:
            inicio.x = 7000.0;
            inicio.y = 10000.0;
            fin.x = 7232.0;
            fin.y = 11072.0;
            fichero = "resources/naufrago.txt";
            personaje   = "Naufrago";
            areaRecorte = sf::IntRect(256,0,127,128);
            break;

        case 4:
            inicio.x = 7000.0;
            inicio.y = 10000.0;
            fin.x = 7232.0;
            fin.y = 11072.0;
            fichero = "resources/preso.txt";
            personaje   = "Preso";
            areaRecorte = sf::IntRect(384,0,127,128);
            break;

        case 5:
            inicio.x = 7000.0;
            inicio.y = 10000.0;
            fin.x = 7232.0;
            fin.y = 11072.0;
            //fichero = "resources/embarazada.txt";
            //personaje   = "Embarazada";
            areaRecorte = sf::IntRect(512,0,127,128);
            break;
    }

    return new Ruta(numRuta, inicio, fin, false, dinero, fichero, personaje, areaRecorte,guia);
}
