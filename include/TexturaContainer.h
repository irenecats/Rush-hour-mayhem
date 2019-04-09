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

        void crearTextura(std::string &url);
        sf::Texture* getTextura(int num);
    protected:
    private:
        static TexturaContainer* claseTextura;

       std::vector <sf::Texture*> vectorTexturas;
};

#endif // TEXTURACONTAINER_H
