#ifndef NPC_H
#define NPC_H

#include "Interpolacion.h"
#include "Node.h"
#include "Sprite.h"
#include "TexturaContainer.h"
#include "IA.h"
#include "Window.h"
#include <string>
#include <iostream>

class NPC {
public:
    NPC(Node* nodoInicial, IA* intelig);
    virtual ~NPC();

    void update(int time);
    void render(Window &ventana, float ptick);

    void setInterpolaciones (float x, float y);
    void setPosicionesIniciales();


    Sprite Getsprite() {
        return sprite;
    }
    bool Getborrame() {
        return borrame;
    }
    bool Getchoque() {
        return choque;
    }
    void Setchoque(bool val) {
        choque = val;
    }
    sf::RectangleShape GetRectFrenado() {
        return rectFrenado;
    }
    void Setsprite(Sprite val) {
        sprite = val;
    }
    void Setinteligencia(IA* nuevaInteligencia) {
        inteligencia = nuevaInteligencia;
    };
    void frenar();
    void velocidadNormal();

protected:

private:
    static const int RADIO_GIRO = 160;
    Interpolacion posAnterior, posSiguiente;
    Sprite sprite;
    sf::RectangleShape rectFrenado;

    IA* inteligencia;
    Node* nodoInicio, *nodoDestino;

    sf::Vector2i puntoImaginario;
    sf::Vector2i centroGiro;

    float MAX_VEL = 400;
    float velocidad = MAX_VEL; // pixeles por segundo
    int sentidoGiro;
    int anguloNuevo;
    float anguloBarrido;
    int orientacionDeg;

    sf::Vector2i calculaPuntoImaginario(Node* puntoCurva);
    int anguloCalle(Node* inicio, Node* fin);
    int calculaSentidoGiro();
    float calculaAngBarridoInicial();
    bool ceroNegativo(float valor);
    bool estoyRecto();
    bool mePasoMRU(sf::Vector2f posFinalFrame);
    sf::Vector2f posMRU(int tiempoRecto);
    sf::Vector2f damePuntoInicioGiro(Node &nodo);
    sf::Vector2f damePuntoFinGiro(Node &nodo);
    int calculaTiempoRecto();

    float a(float angulo);
    sf::VertexArray debugLine;
    void setDebugLine(Node *nodo1, Node *nodo2);

    bool choque = false;
    bool borrame = false;
    void desvanecerse();
};

#endif // NPC_H
