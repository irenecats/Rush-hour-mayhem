#include "Window.h"

Window::Window() : window(sf::VideoMode(800, 600), "Rush Hour Mayhem"){
}

Window::Window(unsigned int ancho, unsigned int alto, const std::string titulo) : window(sf::VideoMode(ancho, alto), titulo) {

}

Window::~Window() {
    //dtor
}

bool Window::isOpen() {
    return window.isOpen();
}

bool Window::pollEvent(sf::Event &event) {
    return window.pollEvent(event);
}

/* Hecho por Mateo */
/* Si se quiere usar la entrada de texto de otra forma, comenta esta funcion */

int Window::event()
{
    int tecla = sf::Keyboard::Unknown;

    sf::Event event;

    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed :
                window.close();
                break;

            case sf::Event::KeyPressed :
                tecla = event.key.code; // esto NO es ASCII, sino que es un valor que SFML le da a las teclas que considera utiles
                break;

            default :
                // manejar otros eventos
                break;
        }
    }

    return tecla; // si no se presiona ninguna tecla, devuelve sf::Keyboard::Unknown, que es igual a -1
}

/*
    (Mateo)
    Se podria implementar el raton, devolviendo
    una struct que habria que definir, y pasarla
    desde Juego->StateManager->State->StateX, con
    lo necesario para controlar el funcionamiento
    del raton (posicion del cursor, click, etc).
*/

void Window::close() { window.close(); }

void Window::clear(const sf::Color &color) {
    window.clear(sf::Color(color));
}

void Window::display() { window.display(); }

void Window::draw(Sprite &sprite) {
    window.draw(sprite.getSprite());
}

sf::Vector2u Window::getSize() {
    return window.getSize();
}

void Window::draw(sf::RectangleShape &shape){
    window.draw(shape);
}

void Window::draw(sf::Text &text){
    window.draw(text);
}

void Window::setView(sf::View view){
    window.setView(view);
}
void Window::draw(sf::VertexArray &vertex){
    window.draw(vertex);
}
/*
app.pollEvent(event)
app.close()
app.clear();
app.display();
*/
