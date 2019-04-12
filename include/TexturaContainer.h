#ifndef TEXTURACONTAINER_H
#define TEXTURACONTAINER_H
#include <SFML/Graphics.hpp>
#include <iostream>

class TexturaContainer
{
    public:
        TexturaContainer();
        virtual ~TexturaContainer();
        static TexturaContainer* instancia();

        int crearTextura(std::string &url);
        sf::Texture* getTextura(int num);

        int crearTexturaMapa(std::string &url);
        std::vector <sf::Texture*> getTexturaMapa();
    protected:
    private:
        static TexturaContainer* claseTextura;

        std::vector <sf::Texture*> vectorTexturas;
        std::vector <sf::Texture*> vectorTexturasMapa;
};

#endif // TEXTURACONTAINER_H
