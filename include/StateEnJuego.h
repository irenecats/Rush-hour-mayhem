#ifndef STATEENJUEGO_H
#define STATEENJUEGO_H

#include "State.h"
#include "Collision.h"
#include <Sprite.h>
#include <iostream>
#include <FactoryRuta.h>
#include <Ruta.h>
#include <Clock.h>
#include <Node.h>
#include <NPC.h>
#include "IACircular.h"


class StateEnJuego : public State
{
    public:

        static StateEnJuego* instance();

        ID_State input(int);
        void update(int tiempo);
        void render(Window&, const float);

        void inicializar();
        void nuevaPartida();
        void cargarPartida();
        void limpiar();
        bool getRuta();

        ~StateEnJuego();

    private:

        static StateEnJuego* instancia;
        FactoryRuta          factoriaRuta;
        Ruta*                ruta;
        sf::RectangleShape*  origen;
        sf::RectangleShape*  destino;
        Clock                reloj;
        bool                 colision;
        bool                 cancionCambiada = false;
        sf::Font             fuente;
        sf::Text             finRuta;
        std::vector<Node*>   nodos;
        std::vector<Node*>   cercanos;
        std::vector<NPC>     npcs;
        sf::VertexArray      linea;
        IACircular           iaCirc;
        sf::VertexArray      guia;

        float* posInicialJugador = nullptr;

        StateEnJuego();
        void buscaCercanos();
        void generaCoches(int tot);
        int  compruebaNPC();
        void detectColisionRuta();
        void detectColisionNPC();
        void detectColisionMapa();
        void recalculaRango();
        void cambiarCancion(std::string nombreCancion, sf::Music musica);
        void encuentraCMC();
        void dibujaGuia();
        sf::RectangleShape colisionGenerarNPC;
};

#endif // STATEENJUEGO_H
