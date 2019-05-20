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
    int tiempo = 0;
    const char* fichero;
    std::string personaje = "";
    sf::IntRect areaRecorte;
    std::vector<sf::Vector2f> guia;

    std::cout << "Antes del switch de numRuta" << std::endl;
    std::cout << "numRuta = " << numRuta << std::endl;

    switch(numRuta){
        case 1:
            inicio.x = 387*32;
            inicio.y = 290*32;
            fin.x = 241*32;
            fin.y = 414*32;


            dinero = 300;
            tiempo = 60;

            fichero = "resources/pija.txt";
            personaje   = "Brittany";  //o tiffany, se aceptan propuestas
            areaRecorte = sf::IntRect(0,0,128,128);
            guia.push_back(sf::Vector2f(387*32,290*32));
            guia.push_back(sf::Vector2f(376*32,290*32));
            guia.push_back(sf::Vector2f(376*32,315*32));
            guia.push_back(sf::Vector2f(303*32,315*32));
            guia.push_back(sf::Vector2f(303*32,328*32));
            guia.push_back(sf::Vector2f(283*32,328*32));
            guia.push_back(sf::Vector2f(283*32,344*32));
            guia.push_back(sf::Vector2f(265*32,344*32));
            guia.push_back(sf::Vector2f(265*32,415*32));
            guia.push_back(sf::Vector2f(242*32,414*32));
            break;

        case 2:

            inicio.x = 408*32;
            inicio.y = 73*32;
            fin.x = 272*32;
            fin.y = 372*32;
		dinero = 300;
            tiempo = 60;

            fichero = "resources/embarazada.txt";
            personaje   = "Janette";
            areaRecorte = sf::IntRect(128,0,124,128);
            guia.push_back(sf::Vector2f(408*32,73*32));
            guia.push_back(sf::Vector2f(419*32,73*32));
            guia.push_back(sf::Vector2f(419*32,36*32));
            guia.push_back(sf::Vector2f(366*32,36*32));
            guia.push_back(sf::Vector2f(366*32,345*32));
            guia.push_back(sf::Vector2f(366*32,363*32));
            guia.push_back(sf::Vector2f(347*32,363*32));
            guia.push_back(sf::Vector2f(347*32,372*32));
            guia.push_back(sf::Vector2f(323*32,372*32));
            guia.push_back(sf::Vector2f(323*32,381*32));
            guia.push_back(sf::Vector2f(303*32,381*32));
            guia.push_back(sf::Vector2f(303*32,372*32));
            guia.push_back(sf::Vector2f(272*32,372*32));
            break;

        case 3:


            inicio.x = 466*32;
            inicio.y = 421*32;
            fin.x = 246*32;
            fin.y = 248*32;
            fichero = "resources/naufrago.txt";
            personaje   = "Robin";
dinero = 300;
            tiempo = 60;
            areaRecorte = sf::IntRect(256,0,127,128);
            guia.push_back(sf::Vector2f(466*32,421*32));
            guia.push_back(sf::Vector2f(466*32,427*32));
            guia.push_back(sf::Vector2f(443*32,427*32));
            guia.push_back(sf::Vector2f(443*32,324*32));
            guia.push_back(sf::Vector2f(431*32,324*32));
            guia.push_back(sf::Vector2f(431*32,310*32));
            guia.push_back(sf::Vector2f(412*32,310*32));
            guia.push_back(sf::Vector2f(412*32,292*32));
            guia.push_back(sf::Vector2f(283*32,293*32));
            guia.push_back(sf::Vector2f(283*32,278*32));
            guia.push_back(sf::Vector2f(265*32,278*32));
            guia.push_back(sf::Vector2f(265*32,254*32));
            guia.push_back(sf::Vector2f(224*32,254*32));
            guia.push_back(sf::Vector2f(224*32,248*32));
            guia.push_back(sf::Vector2f(246*32,248*32));

            break;

        case 4:


            inicio.x = 391*32;
            inicio.y = 500*32;
            fin.x = 134*32;
            fin.y = 56*32;
            fichero = "resources/preso.txt";
            personaje   = "Luke";
dinero = 300;
            tiempo = 60;
            areaRecorte = sf::IntRect(384,0,127,128);
            guia.push_back(sf::Vector2f(391*32,500*32));
            guia.push_back(sf::Vector2f(398*32,500*32));
            guia.push_back(sf::Vector2f(398*32,491*32));
            guia.push_back(sf::Vector2f(442*32,491*32));
            guia.push_back(sf::Vector2f(442*32,324*32));
            guia.push_back(sf::Vector2f(431*32,324*32));
            guia.push_back(sf::Vector2f(431*32,310*32));
            guia.push_back(sf::Vector2f(412*32,310*32));
            guia.push_back(sf::Vector2f(412*32,292*32));
            guia.push_back(sf::Vector2f(283*32,292*32));
            guia.push_back(sf::Vector2f(283*32,278*32));
            guia.push_back(sf::Vector2f(265*32,278*32));
            guia.push_back(sf::Vector2f(265*32,254*32));
            guia.push_back(sf::Vector2f(64*32,254*32));
            guia.push_back(sf::Vector2f(64*32,137*32));
            guia.push_back(sf::Vector2f(72*32,137*32));
            guia.push_back(sf::Vector2f(72*32,70*32));
            guia.push_back(sf::Vector2f(134*32,70*32));
            guia.push_back(sf::Vector2f(134*32,56*32));
            break;

        case 5:
            inicio.x = 433*32;
            inicio.y = 138*32;
            fin.x = 47*32;
            fin.y = 529*32;
            fichero = "resources/uber.txt";
dinero = 300;
            tiempo = 60;
            personaje   = "Travis";
            areaRecorte = sf::IntRect(512,0,127,128);
            guia.push_back(sf::Vector2f(443*32,138*32));
            guia.push_back(sf::Vector2f(450*32,138*32));
            guia.push_back(sf::Vector2f(450*32,153*32));
            guia.push_back(sf::Vector2f(415*32,153*32));
            guia.push_back(sf::Vector2f(415*32,179*32));
            guia.push_back(sf::Vector2f(397*32,179*32));
            guia.push_back(sf::Vector2f(397*32,226*32));
            guia.push_back(sf::Vector2f(370*32,226*32));
            guia.push_back(sf::Vector2f(370*32,234*32));
            guia.push_back(sf::Vector2f(347*32,234*32));
            guia.push_back(sf::Vector2f(347*32,254*32));
            guia.push_back(sf::Vector2f(347*32,293*32));
            guia.push_back(sf::Vector2f(300*32,293*32));
            guia.push_back(sf::Vector2f(300*32,345*32));
            guia.push_back(sf::Vector2f(262*32,345*32));
            guia.push_back(sf::Vector2f(262*32,416*32));
            guia.push_back(sf::Vector2f(238*32,416*32));
            guia.push_back(sf::Vector2f(238*32,454*32));
            guia.push_back(sf::Vector2f(188*32,454*32));
            guia.push_back(sf::Vector2f(188*32,490*32));
            guia.push_back(sf::Vector2f(205*32,490*32));
            guia.push_back(sf::Vector2f(205*32,529*32));
            guia.push_back(sf::Vector2f(47*32,529*32));
            break;
    }

    std::cout << "Creamos la ruta segun los datos aportados por factoryRuta" << std::endl;

    return new Ruta(numRuta, inicio, fin, false, dinero, tiempo, fichero, personaje, areaRecorte,guia);
}
