#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "events_lesson");

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { // Когда внутри optional реально что-то лежит, достать это можно через -> (как с указателем
                window.close();
            }
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) { // auto* key - указатель 
                if (key->code == sf::Keyboard::Key::Escape) {              // потому что getIf действительно возвращает указатель (либо на данные события, либо nullptr, если это не тот тип события)
                    window.close();
                }
            }
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    window.close();
                }
            }
        }
        // std::optional - это тип из стандартной библиотеки C++, которая может содержать значения, либо быть пустой
        // Обычная переменная (int x = 5) всегда что-то содержит — не может быть "и числом, и ничем одновременно"
        // А std::optional<T> — может: либо в ней лежит значение типа T, либо в ней вообще ничего нет
        // optional умеет сам превращаться в true/false

        window.clear(sf::Color::Black);
        window.display();
    }
}
// g++ events_lesson.cpp -o events_lesson.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system