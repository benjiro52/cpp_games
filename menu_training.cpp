#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

enum class GameState {
    Menu,
    Playing, 
    GameOver
}; 
// enum class — это способ создать свой тип с ограниченным набором именованных значений.
// Вместо того чтобы гадать, что значит число 0, 1 или 2, у есть понятные имена
// GameState::Menu куда яснее, чем "переменная равна нулю".

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "menu");
    GameState currentState = GameState::Menu;
    
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        // обработка ошибки — файл шрифта не найден
    }
    sf::Text text(font, "testing testing testing", 30); 
    text.setFillColor(sf::Color::White);
    text.setPosition({250.f, 250.f});
    

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (currentState == GameState::Menu) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
                currentState = GameState::Playing;
            }
        } else if (currentState == GameState::Playing) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
                currentState = GameState::GameOver;
            }
        } else if (currentState == GameState::GameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
                currentState = GameState::Menu;
            }
        }

        if (currentState == GameState::Menu) {
            window.clear(sf::Color::Black);
            window.draw(text);
        } else if (currentState == GameState::Playing) {
            window.clear(sf::Color::Red);
            window.draw(text);
        } else if (currentState == GameState::GameOver) {
            window.clear(sf::Color::Blue);
            window.draw(text);
        }

        window.display();
    }
}
// g++ menu_training.cpp -o menu_training.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
// where is my commit?