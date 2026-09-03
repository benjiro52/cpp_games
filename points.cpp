#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

enum class GameState {
    Menu,
    Playing, 
    GameOver
}; 

class PLayer {

};

class Obstacle {
    
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "preparing1");
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }


    }
}