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

        void crearTextura(std::string &url, std::string nombreTextura);
        sf::Texture* getTextura(std::string nombreTextura);

        int crearTexturaMapa(std::string &url);
        std::vector <sf::Texture*> getTexturaMapa();
    protected:
    private:
        static TexturaContainer* claseTextura;

        std::map<std::string, sf::Texture*> mapaTexturas;
        std::vector <sf::Texture*> vectorTexturasMapa;
};

#endif // TEXTURACONTAINER_H
