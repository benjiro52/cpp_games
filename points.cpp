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

class Obstacle {
private:
    sf::RectangleShape obstacle;
public:

};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "preparing1");
    GameState currentState = GameState::Menu;

    // text
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        // обработка ошибки, если файл не найден
    }
    sf::Text text(font, "Welcome to preparing1. Press Enter to continue", 30);
    text.setFillColor(sf::Color::White);
    text.setPosition({50.f, 250.f});

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        
        if (currentState == GameState::Menu) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                currentState = GameState::Playing;
            }
        }

        if (currentState == GameState::Menu) {
            window.clear(sf::Color::Black);
            window.draw(text);
        }
        if (currentState == GameState::Playing) {
            window.clear(sf::Color::Black);



            
        }
        window.display();
    }
}
// g++ points.cpp -o points.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system