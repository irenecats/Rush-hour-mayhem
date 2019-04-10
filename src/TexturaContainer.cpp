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
    if(!vectorTexturas.empty()){
        for (sf::Texture* text:vectorTexturas){
            if(text) delete text;
            text = nullptr;
        }

        vectorTexturas.clear();
    }
}


int TexturaContainer::crearTextura(std::string &url){
    sf::Texture *text = new sf::Texture;
    if(!text->loadFromFile(url)){
        text = nullptr;
    }
    vectorTexturas.push_back(text);

    return vectorTexturas.size()-1;
}

int TexturaContainer::crearTexturaMapa(std::string &url){
    sf::Texture *text = new sf::Texture;
    if(!text->loadFromFile(url)){
        text = nullptr;
    }
    vectorTexturasMapa.push_back(text);

    return vectorTexturasMapa.size()-1;
}



sf::Texture* TexturaContainer::getTextura(int num){
    if(num>=vectorTexturas.size())
        num = vectorTexturas.size()-1;

    return vectorTexturas[num];
}

std::vector <sf::Texture*> TexturaContainer::getTexturaMapa(){
    return vectorTexturasMapa;
}
