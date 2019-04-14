#include "IACircular.h"

IACircular::IACircular(/*std::vector<Node*> &p_nodos*/) : IA(/*p_nodos*/)
{
    srand(time(NULL));
}

IACircular::~IACircular()
{
    //dtor
}

Node* IACircular::getNextNode(Node &nodoActual) {
    int decision = rand() % nodoActual.adj.size();
    return nodoActual.adj[decision];
}
