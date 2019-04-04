#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Graphics.hpp>


class Sprite //: public sf::Drawable, public sf::Transformable
{
    public:
        Sprite();
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
        //void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void mover(float x, float y);
        void escalar(float x, float y);
        void rotar(float angulo);


    protected:

    private:
        sf::Sprite s;
        float* datosSprite = new float();
};

#endif // SPRITE_H
