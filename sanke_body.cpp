#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Snake {
private:
    sf::RectangleShape rectangle;
    vector<sf::Vector2f> bodyPositions;
public:
    Snake(sf::Vector2f startPos) : rectangle{sf::Vector2f{25.f, 25.f}}{
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "snake_body");
    Snake snake({375.f, 275.f});

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        
        snake.draw(window);
        window.display();
    }
}