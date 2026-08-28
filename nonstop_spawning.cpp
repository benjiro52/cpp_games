#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

// class spawnCircle {
// private:
//     sf::CircleShape circle;
// public:
//     spawnCircle(sf::Vector2f startPos) : circle(50.f) {
//         circle.setFillColor(sf::Color::Red);
//         circle.setPosition(startPos);
//     }

//     void draw(sf::RenderWindow& window) {
//         window.draw(circle);
//     }
// };

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

void spawnPlayer(vector<Player>& player_in_game) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distX(0, 775); // 800 - 25
    uniform_int_distribution<int> distY(0, 575); // 600 - 25

    float x = static_cast<float>(distX(gen));
    float y = static_cast<float>(distY(gen));

    player_in_game.push_back(Player({x, y}));
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "nonstop_spawning");
    // Player player({375.f, 560.f});
    // spawnCircle circle({100.f, 100.f});
    vector<Player> player_in_game;

    sf::Clock clock;
    const float spawnDelay = 0.5f;

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }


        if (clock.getElapsedTime().asSeconds() >= spawnDelay) {
            spawnPlayer(player_in_game);
            clock.restart();
        }
        window.clear(sf::Color::Black);
        for (Player& p : player_in_game) { //fucking spawn
            p.draw(window);
        }
        window.display();
    }
}
// g++ nonstop_spawning.cpp -o nonstop_spawning.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
// i lost