#ifndef NPC_H
#define NPC_H

#include "Interpolacion.h"
#include "Node.h"
#include "Sprite.h"
#include "TexturaContainer.h"
#include "IA.h"
#include "Window.h"
#include <string>

class NPC
{
    public:
        NPC(Node &nodoInicial);
        virtual ~NPC();

        void update(int time);
        void render(Window &ventana, float ptick);

        void setInterpolaciones (Interpolacion val);

        Sprite Getsprite() { return sprite; }
        void Setsprite(Sprite val) { sprite = val; }
        void Setinteligencia(IA* nuevaInteligencia) { inteligencia = nuevaInteligencia; };

    protected:

    private:
        Interpolacion posAnterior, posSiguiente;
        Sprite sprite;
        int refTextura;
        sf::RectangleShape rectFrenado;
        IA* inteligencia;
        Node nodoDestino;

        sf::Vector2i puntoImaginario;
        int sentidoGiro;
        int anguloNuevo;
        int anguloBarrido;

        int anguloCalle(sf::Vector2i inicio, sf::Vector2i fin);
        sf::Vector2i calculaPuntoImaginario();

};

#endif // NPC_H
