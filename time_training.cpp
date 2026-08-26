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
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "time_trainig");
    Player player({375.f, 560.f});

    sf::Clock clock;

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        player.draw(window);
        window.display();
    }
}
// g++ time_training.cpp -o time_training.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system