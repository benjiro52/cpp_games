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

    while (const optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        
    }
}
// g++ menu_training.cpp -o menu_training.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system