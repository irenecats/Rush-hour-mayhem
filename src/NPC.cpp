#include "NPC.h"

NPC::NPC(Node &nodoInicial) : nodoInicio(nodoInicial)
{
    std::string ruta("resources/audi.png");
    TexturaContainer::instancia()->crearTextura(ruta, "Audi");

    sprite.setTextura(TexturaContainer::instancia()->getTextura("Jugador"));
    sprite.setRectTextura(sf::IntRect(1*70 + 5, 1*145 - 12, 70, 117));
    sprite.setOrigin(sprite.getGlobalBounds()[0] / 2, sprite.getGlobalBounds()[1] / 2);
    sprite.setPosition(nodoInicial.getCoorX(),nodoInicial.getCoorY());
    sprite.setScale(0.6f, 0.6f);
/*
    rectFrenado.setSize(sf::Vector2f(50, sprite.getGlobalBounds()[1]));
    rectFrenado.setOrigin(sprite.getGlobalBounds()[0] * -0.70, sprite.getGlobalBounds()[1] / 2);
    rectFrenado.setFillColor(sf::Color::Transparent);
    rectFrenado.setOutlineColor(sf::Color::Red);
    rectFrenado.setOutlineThickness(2);

*/
/*
    puntoImaginario = sf::Vector2i(0, 0);
    posAnterior.Setx(nodoInicio.getCoorX());
    posAnterior.Sety(nodoInicio.getCoorY());
    posSiguiente.Setx(nodoInicio.getCoorX());
    posSiguiente.Sety(nodoInicio.getCoorY());*/

    //anguloNuevo = anguloCalle((sf::Vector2i) lineaInicio[0].position, (sf::Vector2i) lineaInicio[1].position);

}



NPC::~NPC()
{
    //dtor
}

void update(int time) {

};

void NPC::render(Window &ventana, float ptick) {
   // float interPosX = posAnterior.Getx() * (1 - ptick) + posSiguiente.Getx() * ptick;
   // float interPosY = posAnterior.Gety() * (1 - ptick) + posSiguiente.Gety() * ptick;

    //sprite.setPosition(interPosX, interPosY);
    //rectFrenado.setPosition(sprite.getPosition()[0], sprite.getPosition()[1]);
    ventana.draw(sprite);
};

void NPC::setInterpolaciones(Interpolacion val) {
    posAnterior = posSiguiente;
    posSiguiente = val;
}
