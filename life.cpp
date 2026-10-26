#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Life_table {
private: 
    sf::RectangleShape rectangle;
public:

};


int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Life");

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

    }
}
// am i stupid this time????
// g++ life.cpp -o life.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system