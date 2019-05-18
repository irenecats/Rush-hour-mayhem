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

        //Los básicos van del 1 al 4
        case 1:
            id = p_id;
            nombre = "Turbo";
            descripcion = "Proporciona mas velocidad durante un periodo corto de tiempo.";
            precio = 200;
            ruta = "resources/pu1.png";
        break;

        case 2:
            id = p_id;
            nombre = "Mayor manejabilidad";
            descripcion = "El coche hara los giros mas cerrados y sera mas facil la conduccion.";
            precio = 150;
            ruta = "resources/pu2.png";
        break;

        case 3:
            id = p_id;
            nombre = "Radio FM";
            descripcion = "Durante la mision suena musica de fondo que distrae al cliente, y\nasi no se da cuenta de las colisiones.";
            precio = 200;
            ruta = "resources/pu3.png";
        break;

        case 4:
            id = p_id;
            nombre = "Reduccion de retroceso";
            descripcion = "Al chocarse con otros coches de la ciudad, el taxi no se frenara\ntanto.";
            precio = 100;
            ruta = "resources/pu4.png";
        break;

        //Los power-ups especiales van del 5 al 7
        case 5:
            id = p_id;
            nombre = "Lanza cohetes";
            descripcion = "Permite disparar una bala cada vez, la cual es capaz de destruir\ncoches.";
            precio = 500;
            ruta = "resources/pu5.png";
        break;

        case 6:
            id = p_id;
            nombre = "Guia en la carretera";
            descripcion = "Se dibuja el camino mas corto entre la posicion en la que se\nactiva y el destino del cliente.";
            precio = 400;
            ruta = "resources/pu6.png";
        break;

        case 7:
            id = p_id;
            nombre = "Modo fantasma";
            descripcion = "El jugador dejara de colisionar con otros cocher por un periodo de tiempo.";
            precio = 800;
            ruta = "resources/pu7.png";
        break;
    }

    return new PowerUp(p_id, nombre, descripcion, precio, ruta);
}

