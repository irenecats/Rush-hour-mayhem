#include <SFML/Graphics.hpp>
#include <Clock.h>
#include <Window.h>
#include <Sprite.h>
#include <iostream>
#include "Juego.h"
int main()
{
    // Create the main window
    Sprite sprite;
    sprite.escalar(0.5, 1);
    sprite.setPosition(3, 4);

    Juego::Instance()->iniciarJuego();
    //std::cout << sprite.getGlobalBounds()[0] << std::endl;

    return EXIT_SUCCESS;
}
