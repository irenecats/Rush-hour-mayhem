#include "Sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(sf::Texture* textura)
{
    s.setTexture(*textura);
}

Sprite::Sprite(sf::Texture* textura, sf::IntRect ir){
    s.setTexture(*textura);
    setRectTextura(ir);
}

Sprite::~Sprite()
{
    //dtor
}

float* Sprite::getPosition(){
    datosSprite[0] = s.getPosition().x;
    datosSprite[1] = s.getPosition().y;
    return datosSprite;

}

float Sprite::getRotation(){
    return s.getRotation();
}

float* Sprite::getScale(){
    datosSprite[0] = s.getScale().x;
    datosSprite[1] = s.getScale().y;
    return datosSprite;
}

float* Sprite::getOrigin(){
    datosSprite[0] = s.getOrigin().x;
    datosSprite[1] = s.getOrigin().y;
    return datosSprite;
}


float* Sprite::getGlobalBounds(){
    datosSprite[0] = s.getGlobalBounds().width;
    datosSprite[1] = s.getGlobalBounds().height;
    return datosSprite;
}


void Sprite::setPosition(float x, float y){
    s.setPosition(x,y);
}

void Sprite::setRotation(float r){
    s.setRotation(r);
}

void Sprite::setScale(float x, float y){
    s.setScale(x,y);
}

void Sprite::setOrigin(float x, float y){
    s.setOrigin(x,y);
}


void Sprite::mover(float x, float y) {
    s.move(x, y);
}

void Sprite::escalar(float x, float y) {
    s.scale(x, y);
}

void Sprite::rotar(float angulo) {
    s.rotate(angulo);
}

sf::Sprite Sprite::getSprite() {
    return s;
}

void Sprite::setRectTextura(sf::IntRect rect) {
    s.setTextureRect(rect);
}

void Sprite::setTextura(sf::Texture* textura) {
    s.setTexture(*textura);
}
/*
void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(s, states);
}*/
