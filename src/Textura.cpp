#include "Textura.h"

Textura::Textura()
{
    //ctor
}

Textura::~Textura()
{
    //dtor
}

Textura::Textura(std::string ruta) {
    if (!texture.loadFromFile(ruta)) {
        std::cerr << "Error cargando la imagen " << ruta;
        exit(0);
    }
}

sf::Texture Textura::getTextura() { ///mirar como mejorar esto
    return texture;
}
