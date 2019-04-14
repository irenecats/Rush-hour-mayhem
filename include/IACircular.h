#ifndef IACIRCULAR_H
#define IACIRCULAR_H

#include <stdlib.h>
#include <time.h>
#include <IA.h>
#include "Node.h"


class IACircular : public IA
{
    public:
        IACircular(/*std::vector<Node*> &p_nodos*/);
        virtual ~IACircular();

        virtual Node* getNextNode(Node &nodoActual);
    protected:

    private:
};

#endif // IACIRCULAR_H
