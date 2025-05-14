#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow renderWindow{ sf::VideoMode(sf::Vector2u(100,100)), "My Window" };
    std::cout << "Hello world!\n";
}