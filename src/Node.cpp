#include <iostream>
#include <stdio.h>
#include "Node.h"

using namespace std;

    Node::Node(){}
    Node::Node(int x,int y){
        coor[0]=x;
        coor[1]=y;
        coste = 0;
        distanciaH = -1;
    }
    void Node::setCoorX(int x){
        coor[0]=x;
    }
    void Node::setCoorY(int y){
        coor[1]=y;
    }
    int Node::getCoorX(){
        return coor[0];
    }
    int Node::getCoorY(){
        return coor[1];
    }
    void Node::addAdj(Node* nuevo){
        adj.push_back(nuevo);
    }
    int Node::getSize(){
        return adj.size();
    }
    void Node::setParent(Node* parent){
        padre = parent;
        coste = parent->getCoste()+10;
    }

    int Node::getDistancia(sf::Vector2f fin){
        if(distanciaH == -1){
             distanciaH = abs(coor[0] - fin.x)+abs(coor[1]- fin.y);
        }
        return distanciaH;
    }
    int Node::getCoste(){
        return coste;
    }
    bool Node::compare(Node* otro){
        bool iguales=false;

        if(coor[0] == otro->getCoorX() && coor[1]==otro->getCoorY()){
            iguales = true;
        }
        return iguales;
    }
