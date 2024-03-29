#ifndef RUTA_H
#define RUTA_H
#include <SFML/Graphics.hpp>
#include "TexturaContainer.h"
#include <Clock.h>
#include <Window.h>
#include <iostream>
#include <Sprite.h>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdlib>

class Ruta
{
    public:
        Ruta();
        Ruta(int id, sf::Vector2f inicio, sf::Vector2f fin, bool client, int dinero, int tiempo, const char* titulo, std::string name, sf::IntRect areaRecorte,std::vector<sf::Vector2f>);
        virtual         ~Ruta();

        void            haTerminado();
        void            haLlegado();
        void            pasarDialogo();
        void            RenderPuntos(Window& window);
        void            RenderDialogos(Window& window);
        void            Update(Clock& tiempo);
        int             getID();
        bool            getActiva();
        bool            getTerminada();
        int             getDiagActual();
        void            setDiagActual(int tipo);
        int             getTiempoMax() { return tiempoMax; }
        int             getDineroMax() { return dineroMax; }
        int             tiempoAcumulado = 0;

        sf::RectangleShape*   getOrigen();
        sf::RectangleShape*   getDestino();
        std::vector<sf::Vector2f> getGuia();

    protected:
    private:
        //General
        int idRuta;
        std::string nombreCliente;
        sf::RectangleShape*  origen;
        sf::RectangleShape*  destino;
        int                  dineroMax;
        int                  tiempoMax;
        bool                 activa;
        bool                 terminada;
        bool                espacioPulsado = false;
        std::vector<sf::Vector2f> guia;
        //Dialogo
        sf::Text            nombre;
        sf::Text            dialogo;
        Sprite              cajaDialogo;
        sf::Font            fuente;
        int                 DiagActual;// 0 = Sin dialogo; 1 = Dialogo introduccion; 2 = Dialogo de choque;
        int                 letra;
        int                 numfrase;
        int                 tex;
        //Cliente
        Sprite                           cliente;
        std::vector <std::string>        dialogointro;
        std::vector <std::string>        dialogochoque;

        static bool crearPersonajesDialogo;

        void leefichero(const char* titulo);
        void cambiaEstiloDialogo();
};

#endif // RUTA_H
