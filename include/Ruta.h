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
        Ruta(int id, sf::Vector2f inicio, sf::Vector2f fin, bool client, int dinero, char* titulo, std::string name, sf::IntRect areaRecorte);
        virtual         ~Ruta();
        int             getDiag();
        bool            getActiva();
        sf::RectangleShape*   getOrigen();
        sf::RectangleShape*   getDestino();
        sf::Text        getNombre();
        sf::Text        getDialogo();
        int             getDiagActual();
        void            setDiagActual(int tipo);
        std::vector <std::string>        getFrasesIni();
        void            haLlegado();
        void            pasarDialogo();

        void RenderPuntos(Window& window);
        void RenderDialogos(Window& window);
        void Update(Clock& tiempo);

    protected:
    private:
        int idRuta;
        std::string nombreCliente;
        sf::RectangleShape*  origen;
        sf::RectangleShape*  destino;
        int                  dineroMax;
        bool                 activa;
        //Cliente
        Sprite              cliente;
        std::vector <std::string>        dialogointro;
        std::vector <std::string>        dialogochoque;
        //Dialogo
        sf::Text            nombre;
        sf::Text            dialogo;
        Sprite          cajaDialogo;
        sf::Font            fuente;
        int                 DiagActual;
        int                 letra;
        int                 numfrase;
        int                 tex;

        void leefichero(char* titulo);
        void cambiaEstiloDialogo();
};

#endif // RUTA_H
