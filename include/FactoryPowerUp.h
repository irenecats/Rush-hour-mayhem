#ifndef FACTORYPOWERUP_H
#define FACTORYPOWERUP_H
#include "PowerUp.h"

class FactoryPowerUp
{
    public:
        FactoryPowerUp();
        virtual ~FactoryPowerUp();
        PowerUp* crearPowerUp(int p_id);

    protected:

    private:
        int id;
        std::string nombre;
        std::string descripcion;
        std::string ruta;
        int precio;
};

#endif // FACTORYPOWERUP_H
