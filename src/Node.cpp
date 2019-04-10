#include <iostream>
#include <stdio.h>
#include "Node.h"

using namespace std;

    Node::Node(){}
    Node::Node(int x,int y){
        coor[0]=x;
        coor[1]=y;
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
