#include "TexturaContainer.h"

TexturaContainer* TexturaContainer::claseTextura = nullptr;

TexturaContainer* TexturaContainer::instancia() {
    if(claseTextura == nullptr)
        claseTextura = new TexturaContainer();

    return claseTextura;
}

TexturaContainer::TexturaContainer()
{
    //ctor
}

TexturaContainer::~TexturaContainer()
{
    //dtor
}

void TexturaContainer::crearTextura(std::string &url){
    sf::Texture *text = new sf::Texture;
    if(!text->loadFromFile(url)){
        text = nullptr;
    }
    vectorTexturas.push_back(text);
}

sf::Texture* TexturaContainer::getTextura(int num){
    if(num>=vectorTexturas.size())
        num = vectorTexturas.size()-1;

    return vectorTexturas[num];
}
