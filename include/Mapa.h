#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Node.h"
#include "TexturaContainer.h"
#include "Sprite.h"
#include "Window.h"

class Mapa{
    static Mapa* instancia;
    //Grafo de nodos y mapa por capas
    std::vector<Node*> nodos;
    Sprite**** dibujar;


    //Variables de tamaño del mapa por capas
    int _width;
    int _height;
    int numlayer;

    public:
    Mapa();


    static Mapa* Instance();
    std::vector<Node*> getGrafo();
    Sprite**** getMapa();
    void destructorMapa();
    void destructorGrafo();
    void renderMapaAbajo(Window &window);
    void renderMapaArriba(Window &window);
    int  getNumlayer();
    int  getWidth();
    int  getHeight();
};
#endif
