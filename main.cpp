#include <SFML/Graphics.hpp>
#include <Clock.h>
#include <Window.h>
#include <iostream>
int main()
{
    // Create the main window
    Window app(800, 600, "SFML window");

    Clock reloj;


	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        std::cout << reloj.getElapsedTime() << std::endl;
        // Clear screen
        app.clear();

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
