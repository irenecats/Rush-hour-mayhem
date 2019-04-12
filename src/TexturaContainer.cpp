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
///No se si se puede hacer el delete de esto así ahora que es un map y no un vetor
TexturaContainer::~TexturaContainer()
{/*
    if(!mapaTexturas.empty()){
        for (sf::Texture* text:mapaTexturas){
            if(text) delete text;
            text = nullptr;
        }

        mapaTexturas.clear();
    }*/
}


void TexturaContainer::crearTextura(std::string &url, std::string nombreTextura){
    sf::Texture *text = new sf::Texture;
    if(!text->loadFromFile(url)){
        text = nullptr;
    }
    mapaTexturas[nombreTextura] = text;

}

int TexturaContainer::crearTexturaMapa(std::string &url){
    sf::Texture *text = new sf::Texture;
    if(!text->loadFromFile(url)){
        text = nullptr;
    }
    vectorTexturasMapa.push_back(text);

    return vectorTexturasMapa.size()-1;
}



sf::Texture* TexturaContainer::getTextura(std::string nombreTextura){

    if (mapaTexturas.find(nombreTextura) != mapaTexturas.end() ) {
        return mapaTexturas[nombreTextura];
    } else {
        return NULL;
    }
}

std::vector <sf::Texture*> TexturaContainer::getTexturaMapa(){
    return vectorTexturasMapa;
}
