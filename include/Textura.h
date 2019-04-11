#ifndef TEXTURA_H
#define TEXTURA_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Textura
{
    public:
        Textura();
        Textura(std::string ruta);
        virtual ~Textura();

        sf::Texture getTextura();

    protected:

    private:
        sf::Texture texture;
};

#endif // TEXTURA_H
