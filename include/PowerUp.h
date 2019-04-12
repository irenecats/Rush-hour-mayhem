#ifndef POWERUP_H
#define POWERUP_H
#include "Sprite.h"
#include "TexturaContainer.h"
#include <iostream>

class PowerUp
{
    public:
        PowerUp();
        virtual ~PowerUp();

        PowerUp(int p_id, std::string p_nom, std::string p_descrip, int p_precio, std::string ruta);

        int getId();
        std::string getNombre();
        std::string getDescripcion();
        int getPrecio();
        Sprite* getSpritePU();

    protected:

    private:
        int id;
        std::string nombre;
        std::string descripcion;
        int precio;
        Sprite* sprite;
};

#endif // POWERUP_H
