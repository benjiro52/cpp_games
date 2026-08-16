#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800,600}), "sfml_lesson");

    sf::RectangleShape player({20.f, 20.f});
    player.setFillColor(sf::Color::White);
    player.setPosition({375.f, 275.f});

    sf::Vector2f pos = player.getPosition(); //sf::Vector2f — это структура с двумя полями: x и y (оба float). Обращаться к ним просто через точку:
    pos.x;
    pos.y;
    float speed = 0.1f; // сколько пикселей двигаться за один кадр

    while (window.isOpen()) {
        while(const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (player.getPosition().y - speed >= 0.f) {
                player.move({0.f, -speed});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (player.getPosition().y + 20.f + speed <= 600.f) {
                player.move({0.f, speed});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (player.getPosition().x - speed >= 0.f) {
                player.move({-speed, 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (player.getPosition().x + 20.f + speed <= 800.f) {
                player.move({speed, 0.f});
            }
        }

        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }
    // g++ mv_lesson.cpp -o mv_lesson.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
}