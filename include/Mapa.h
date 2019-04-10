#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Node.h"
#include "TexturaContainer.h"
#include "Sprite.h"

class Mapa{
    Mapa* instancia=nullptr;
    //Grafo de nodos y mapa por capas
    std::vector<Node*> nodos;
    Sprite**** dibujar;
    //Variables de tamaño del mapa por capas
    int numlayer;
    int _width;
    int _height;

    public:
    Mapa();
    Mapa* Instance();
    std::vector<Node*> getGrafo();
    Sprite**** getMapa();
    void destructorMapa();
    void destructorGrafo();
};
#endif
