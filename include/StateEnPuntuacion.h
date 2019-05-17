#ifndef STATEENPUNTUACION_H
#define STATEENPUNTUACION_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "State.h"
#include "Sprite.h"
#include "TexturaContainer.h"
#include "StateEnJuego.h"

class StateEnPuntuacion : public State
{
public:

    static StateEnPuntuacion* instance();

    ID_State input(int);
    void update();
    void render(Window&, const float);

    void inicializar();
    void limpiar();

    ~StateEnPuntuacion();

private:

    static StateEnPuntuacion* instancia;
    StateEnPuntuacion();

    float porcentaje = 0.f;
    float dinero = 0.f;

    //Datos de ejemplo de una misión
    int col = 15;
    int tiemp = 80;
    int tiempoPerf = 60;
    int dineroPerf = 350;

    sf::Font* fuente;
    sf::Text* resultados;
    sf::Text* colisiones;
    sf::Text* tiempo;

    sf::Text* ncoli;
    sf::Text* ntiemp;
    sf::Text* ndinero;
    sf::Text* dineroObtenido;

    //Para la barra de porcentaje
    sf::RectangleShape* rect;
    sf::RectangleShape* relleno;

    //Son contadores que se usan para el efecto de los números incrementando
    int c = 0;
    int t = 0;
    int d = 0;

    bool finjuego = false;
    std::vector<std::vector<std::string>> rango;
    std::string currentTime;
    int        currentPos;
    Sprite         fondo;
    sf::Text titulo;
    sf::Text numeros;
    sf::Text fecha;
    sf::Text puntos;
    Sprite          flecha;
    Sprite          oro;
    Sprite          plata;
    Sprite          bronce;

    void calcularPuntuacion (int colisiones, float tiempo, float tiempoPerfecto, float dineroPerfecto);
    void crearText(sf::Text*& text, std::string str, int tamanyo, float x, float y);
    void muestraFinal();
    void leeFichero();
    void organizaRanking();

};

#endif // STATEENPUNTUACION_H
