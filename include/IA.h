#ifndef IA_H
#define IA_H
#include <vector>
#include "Node.h"

class IA
{
    public:
        virtual ~IA();
        virtual Node* getNextNode(Node &nodoActual) = 0;
    protected:
        //std::vector<Node*> *nodos;

        IA(/*std::vector<Node*> &p_nodos*/);
    private:
};

#endif // IA_H
