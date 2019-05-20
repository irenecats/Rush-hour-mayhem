#ifndef STATEENPUNTUACION_H
#define STATEENPUNTUACION_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "State.h"
#include "Sprite.h"
#include "TexturaContainer.h"
#include "StateEnJuego.h"
#include "StateEnTienda.h"

class StateEnPuntuacion : public State
{
public:

    static StateEnPuntuacion* instance();

    ID_State input(int);
    void update(int tiempo);
    void update();

    void render(Window&, const float);

    void inicializar();
    void limpiar();
    void setColisiones(int numero);
    void setTiempo(int segundos);
    void setDineroPerf(int numero);
    void setTiempoPerf(int numero);
    void calcularPuntuacion();

    ~StateEnPuntuacion();

private:

    static StateEnPuntuacion* instancia;
    StateEnPuntuacion();
    bool cancionCambiada = false;

    float porcentaje = 0.f;
    float dinero = 0.f;

    //Datos de ejemplo de una misión
    int col = 0;
    int tiemp = 0;
    int tiempoPerf = 0;
    int dineroPerf = 0;

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

    void crearText(sf::Text*& text, std::string str, int tamanyo, float x, float y);
    void muestraFinal();
    void leeFichero();
    void organizaRanking();

};

#endif // STATEENPUNTUACION_H
