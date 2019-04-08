#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <SFML/Graphics.hpp>


class Window
{
    public:
        Window();
        Window(unsigned int ancho, unsigned int alto, const std::string titulo);
        virtual ~Window();

        bool isOpen();
        bool pollEvent(sf::Event &event);

        /* Mateo se ha inmiscuido aqui */
        /*  He anadido esto que caza los eventos */
        int event();
        /*  En caso de detectar una tecla pulsada, devuelve su valor de sf::Keyboard */
        /* "pollEvent()" no se usaria si utilizamos "event()" */

        void close();
        void clear(const sf::Color &color = sf::Color(0, 0, 0, 255));
        void display();

    protected:

    private:
        sf::RenderWindow window;
};
/*
app.pollEvent(event)
app.close()
app.clear();
app.display();
*/
#endif // WINDOW_H
