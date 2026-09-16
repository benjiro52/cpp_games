#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Snake {

};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake");

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }


    }
}