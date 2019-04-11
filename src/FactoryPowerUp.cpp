#include "FactoryPowerUp.h"

FactoryPowerUp::FactoryPowerUp()
{
    //ctor
}

FactoryPowerUp::~FactoryPowerUp()
{
    //dtor
}

PowerUp* FactoryPowerUp::crearPowerUp(int p_id) {

    switch(p_id) {

        case 1:
            id = p_id;
            nombre = "Turbo";
            descripcion = "Proporciona más velocidad durante un periodo\n corto de tiempo.";
            precio = 200;
            ruta = "resources/lola.jpg";
        break;

        case 2:
            id = p_id;
            nombre = "Lanza cohetes";
            descripcion = "Permite disparar una bala cada vez, que\npuede destruir coches.";
            precio = 500;
            ruta = "resources/lola.jpg";
        break;

        case 3:
            id = p_id;
            nombre = "Radio FM";
            descripcion = "Durante la misión suena música de fondo\nque distrae al cliente, y así no se da cuenta de\n las colisiones.";
            precio = 500;
            ruta = "resources/lola.jpg";
        break;
    }

    return new PowerUp(p_id, nombre, descripcion, precio, ruta);
}

