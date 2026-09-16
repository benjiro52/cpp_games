#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

// Разобраться короче

class Snake {
private:
    sf::RectangleShape rectangle;
public:
    Snake(sf::Vector2f startPos) : rectangle{sf::Vector2f{25.f, 25.f}} {
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
    }

    void movement(float speed, float deltaTime) {
        float distance = speed * deltaTime; 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (rectangle.getPosition().y - distance >= 0.f) {
                rectangle.move({0.f, -distance});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (rectangle.getPosition().y + 25.f + distance <= 600.f) {
                rectangle.move({0.f, distance});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (rectangle.getPosition().x - distance >= 0.f) {
                rectangle.move({-distance, 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (rectangle.getPosition().x + 25.f + distance <= 800.f) {
                rectangle.move({distance, 0.f});
            }
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "preparing3");

    Snake snake({375.f, 275.f});
    sf::Clock deltaClock;
    float snake_speed = 300.f;

    while(window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();

        window.clear(sf::Color::Black);
        snake.draw(window);
        snake.movement(snake_speed, deltaTime);
        window.display();
    }
}
// g++ snake_body.cpp -o snake_body.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system