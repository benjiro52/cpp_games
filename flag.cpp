#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::RectangleShape black_rectangle({400.f, 50.f});
    black_rectangle.setFillColor(sf::Color::Black);
    black_rectangle.setPosition({200.f, 225.f});

    sf::RectangleShape red_rectangle({400.f, 50.f});
    red_rectangle.setFillColor(sf::Color::Red);
    red_rectangle.setPosition({200.f, 275.f});

    sf::RectangleShape gold_rectangle({400.f, 50.f});
    gold_rectangle.setFillColor(sf::Color(255, 206, 0)); // официальный оттенок золотого флага Германии
    gold_rectangle.setPosition({200.f, 325.f});

    // Создаём окно 800x600 пикселей
    sf::RenderWindow window(sf::VideoMode({800,600}), "sfml_lesson");
    while (window.isOpen()) {
        while(const optional event = window.pollEvent()) {
            // Обрабатываем события (закрытие окна, нажатия клавиш и т.д.)
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        // sf::CircleShape circle(50.f); // circle 50
        // circle.setFillColor(sf::Color::Green);
        // circle.setPosition({100.f, 100.f});
        window.clear(sf::Color(128, 128, 128));
        window.draw(black_rectangle);
        window.draw(red_rectangle);
        window.draw(gold_rectangle);
        window.display();
    }
    // g++ flag.cpp -o flag.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
    return 0;
}