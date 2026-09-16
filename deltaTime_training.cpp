#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Player {
private:
    sf::RectangleShape rectangle;
public:
    Player(sf::Vector2f startPos) : rectangle{sf::Vector2f{25.f, 25.f}} {
        rectangle.setFillColor(sf::Color::White);
        rectangle.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(rectangle);
    }

    void movement(float speed, float deltaTime) {
        float distance = speed * deltaTime; // сколько реально пройти в этом кадре

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
    sf::RenderWindow window(sf::VideoMode({800, 600}), "preparing1");

    sf::Clock deltaClock; // this is new
    Player player({375.f, 275.f});
    float player_speed = 200.f;

    while(window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        float deltaTime = deltaClock.restart().asSeconds(); // and this also
        window.clear(sf::Color::Black);
        player.draw(window);
        player.movement(player_speed, deltaTime);
        window.display();
    }
}
// g++ deltaTime_training.cpp -o deltaTime_training.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
// how far am i from snake??????