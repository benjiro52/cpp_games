#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Создаём окно 800x600 пикселей
    sf::RenderWindow window(sf::VideoMode({800,600}), "sfml_lesson");
    while (window.isOpen()) {
        while(const optional event = window.pollEvent()) {
            // Обрабатываем события (закрытие окна, нажатия клавиш и т.д.)
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        // Очищаем экран (заливаем цветом)
        window.clear(sf::Color::Black);
        // Показываем то, что нарисовали
        window.display();
    }

    

    return 0;
}