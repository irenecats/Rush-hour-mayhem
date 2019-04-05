#include "Window.h"
#define WINDOW_H
#include <string>
#include <SFML/Graphics.hpp>

Window::Window() : window(sf::VideoMode(800, 600), "SFML window"){
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

void Window::close() { window.close(); }

void Window::clear(const sf::Color &color) {
    window.clear(sf::Color(color));
}

void Window::display() { window.display(); }
/*
app.pollEvent(event)
app.close()
app.clear();
app.display();
*/
