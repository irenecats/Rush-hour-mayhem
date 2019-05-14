#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>
#include <iostream>


class Sprite //: public sf::Drawable, public sf::Transformable
{
    public:
        Sprite(sf::Texture* textura);
        Sprite();
        Sprite(sf::Texture* textura, sf::IntRect ir);
        virtual ~Sprite();

        float getRotation();
        float* getPosition();
        float* getScale();
        float* getOrigin();
        float* getGlobalBounds();

        void setPosition(float x, float y);
        void setRotation(float r);
        void setScale(float x, float y);
        void setOrigin(float x, float y);
        void setColor(sf::Color);

        void setTextura(sf::Texture* textura);
        void setRectTextura(sf::IntRect rect);

        void mover(float x, float y);
        void escalar(float x, float y);
        void rotar(float angulo);

        sf::Sprite getSprite();

    protected:

    private:
        sf::Sprite s;
        sf::Texture tx;
        float* datosSprite = new float();
};

#endif // SPRITE_H
