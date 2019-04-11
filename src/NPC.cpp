#include "NPC.h"

NPC::NPC(Node &nodoInicial) : nodoDestino(nodoInicial)
{
    std::string ruta("resources/audi.png");
    refTextura = TexturaContainer::instancia()->crearTextura(ruta);
    sprite.setTextura(TexturaContainer::instancia()->getTextura(refTextura));
    sprite.setOrigin(sprite.getGlobalBounds()[0] / 2, sprite.getGlobalBounds()[1] / 2);
    rectFrenado.setSize(sf::Vector2f(50, sprite.getGlobalBounds()[1]));
    rectFrenado.setOrigin(sprite.getGlobalBounds()[0] * -0.70, sprite.getGlobalBounds()[1] / 2);
    rectFrenado.setFillColor(sf::Color::Transparent);
    rectFrenado.setOutlineColor(sf::Color::Red);
    rectFrenado.setOutlineThickness(2);

    puntoImaginario = sf::Vector2i(0, 0);
    posAnterior.Setx(nodoDestino.getCoorX());
    posAnterior.Sety(nodoDestino.getCoorY());
    posSiguiente.Setx(nodoDestino.getCoorX());
    posSiguiente.Sety(nodoDestino.getCoorY());

    anguloNuevo = anguloCalle((sf::Vector2i) lineaInicio[0].position, (sf::Vector2i) lineaInicio[1].position);
}

NPC::~NPC()
{
    //dtor
}

void update(int time) {

};

void render(Window &ventana, float ptick) {

};

void NPC::setInterpolaciones(Interpolacion val) {
    posAnterior = posSiguiente;
    posSiguiente = val;
}
