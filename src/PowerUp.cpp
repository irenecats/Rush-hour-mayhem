#include "PowerUp.h"

PowerUp::PowerUp(int p_id, std::string p_nom, std::string p_descrip, int p_precio, std::string ruta) {
    id = p_id;
    nombre = p_nom;
    descripcion = p_descrip;
    precio = p_precio;
    TexturaContainer::instancia()->crearTextura(ruta, "PowerUps");
    sprite = new Sprite(TexturaContainer::instancia()->getTextura("PowerUps"));
}

PowerUp::PowerUp()
{
    //ctor
}

PowerUp::~PowerUp()
{
    //dtor
}

int PowerUp::getId() {  return id;  }
std::string PowerUp::getNombre() {  return nombre;   }
std::string PowerUp::getDescripcion() {  return descripcion;  }
int PowerUp::getPrecio() {  return precio;  }
Sprite* PowerUp::getSpritePU() {  return sprite;  }
