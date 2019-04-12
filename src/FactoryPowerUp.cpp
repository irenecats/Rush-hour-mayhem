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
            ruta = "resources/lola.jpg";
        break;

        case 2:
            id = p_id;
            nombre = "Mayor manejabilidad";
            descripcion = "El coche hara los giros mas cerrados y sera mas facil la conduccion.";
            precio = 150;
            ruta = "resources/lola.jpg";
        break;

        case 3:
            id = p_id;
            nombre = "Radio FM";
            descripcion = "Durante la mision suena musica de fondo que distrae al cliente, y\nasi no se da cuenta de las colisiones.";
            precio = 200;
            ruta = "resources/lola.jpg";
        break;

        case 4:
            id = p_id;
            nombre = "Reduccion de retroceso";
            descripcion = "Al chocarse con otros coches de la ciudad, el taxi no se frenara\ntanto.";
            precio = 100;
            ruta = "resources/lola.jpg";
        break;

        //Los power-ups especiales van del 5 al 7
        case 5:
            id = p_id;
            nombre = "Lanza cohetes";
            descripcion = "Permite disparar una bala cada vez, la cual es capaz de destruir\ncoches.";
            precio = 500;
            ruta = "resources/lola.jpg";
        break;

        case 6:
            id = p_id;
            nombre = "Guia en la carretera";
            descripcion = "Se dibuja el camino mas corto entre la posicion en la que se\nactiva y el destino del cliente.";
            precio = 400;
            ruta = "resources/lola.jpg";
        break;

        case 7:
            id = p_id;
            nombre = "Modo ambulancia";
            descripcion = "Los coches se iran apartando para dejar paso al coche, que\nse convertira en una ambulancia.";
            precio = 800;
            ruta = "resources/lola.jpg";
        break;
    }

    return new PowerUp(p_id, nombre, descripcion, precio, ruta);
}

