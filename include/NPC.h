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
        NPC(Node* nodoInicial, IA* intelig);
        virtual ~NPC();

        void update(int time);
        void render(Window &ventana, float ptick);

        void setInterpolaciones (float x, float y);

        Sprite Getsprite() { return sprite; }
        void Setsprite(Sprite val) { sprite = val; }
        void Setinteligencia(IA* nuevaInteligencia) { inteligencia = nuevaInteligencia; };

    protected:

    private:
        static const int RADIO_GIRO = 40;

        Interpolacion posAnterior, posSiguiente;
        Sprite sprite;
        sf::RectangleShape rectFrenado;

        IA* inteligencia;
        Node* nodoInicio, *nodoDestino;

        sf::Vector2i puntoImaginario;
        sf::Vector2i centroGiro;
        sf::Vector2i puntoInicioGiro;
        sf::Vector2i puntoFinGiro;

        int velocidad = 10; // pixeles por segundo
        int sentidoGiro;
        int anguloNuevo;
        int anguloBarrido;
        int orientacionDeg;

        sf::Vector2i calculaPuntoImaginario(Node* puntoCurva);
        int anguloCalle(Node* inicio, Node* fin);
        int calculaSentidoGiro();
        float calculaAngBarridoInicial();
        bool ceroNegativo(float valor);
        bool estoyRecto();
        bool mePaso(Node* inicio, Node* fin);
        sf::Vector2f posMRU(int tiempoRecto);
        sf::Vector2f puntoInicioGiro(Nodo &nodo);
        sf::Vector2f puntoFinGiro(Nodo &nodo);
        int calculaTiempoRecto();
};

#endif // NPC_H
