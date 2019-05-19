#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Node{
    public:
    int coor[2]={0,0};
    std::vector<Node*> adj;
    Node* padre;
    int coste;
    int distanciaH;


    Node();
    Node(int x,int y);
    void setCoorX(int x);
    void setCoorY(int y);
    int getCoorX();
    int getCoorY();
    void addAdj(Node* nuevo);
    int getSize();
    void setParent(Node* parent);
    int getCoste();
    int getDistancia(sf::Vector2f);
    bool compare(Node* otro);
};
#endif
