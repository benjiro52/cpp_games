#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "points_easy");
    int clicks = 0;

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        // обработка ошибки, если файл не найден
    }
    sf::Text text(font, "Clicks: ", 30);
    text.setFillColor(sf::Color::White);
    text.setPosition({50.f, 250.f});


    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (clicks == 1000000) {
            text.setString("Congratulations, you are crazy)");
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            clicks += 1;
            text.setString("Click: " + to_string(clicks));
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
            clicks += 500000;
            text.setString("Click: " + to_string(clicks));
        }
    
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }
}
// g++ points_easy.cpp -o points_easy.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
// sami ispravleyte