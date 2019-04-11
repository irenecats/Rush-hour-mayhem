#ifndef FACTORYRUTA_H
#define FACTORYRUTA_H
#include <Ruta.h>
#include <string>

class FactoryRuta
{
    public:
        FactoryRuta();
        virtual ~FactoryRuta();
        Ruta* creaRuta(int numRuta);
    protected:
    private:
};

#endif // FACTORYRUTA_H
