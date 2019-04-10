#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <iostream>
#include <vector>

class Node{
    public:
    int coor[2]={0,0};
    std::vector<Node*> adj;

    Node();
    Node(int x,int y);
    void setCoorX(int x);
    void setCoorY(int y);
    int getCoorX();
    int getCoorY();
    void addAdj(Node* nuevo);
    int getSize();
};
#endif
