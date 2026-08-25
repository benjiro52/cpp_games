#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Rain {
private:
    sf::CircleShape raindrop;
public: 
    Rain(sf::Vector2f startPos) : raindrop{20.f}{
        raindrop.setFillColor(sf::Color(128, 128, 128));
        raindrop.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(raindrop);
    }

    void movementRain() {
        float speed = 0.11f;
        // if (raindrop.getGlobalBounds().position.y + raindrop.getGlobalBounds().size.y + speed <= 600.f) { 
        //     raindrop.move({0.f, speed});
        // }
        raindrop.move({0.f, speed});
    }

    sf::FloatRect getBounds() {
        return raindrop.getGlobalBounds();
    }

};

void Movement(sf::RectangleShape& player, float speed) {
    const float topLimit = 400.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        if (player.getPosition().y - speed >= topLimit) {
            player.move({0.f, -speed});
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if (player.getPosition().y + 40.f + speed <= 600.f) {
            player.move({0.f, speed});
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (player.getPosition().x - speed >= 0.f) {
            player.move({-speed, 0.f});
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (player.getPosition().x + 40.f + speed <= 800.f) {
            player.move({speed, 0.f});
        }
    }
}


void rainRandomSpawn(vector<Rain>& rain) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distX(0, 760);
    uniform_int_distribution<int> distY(0, 10);

    float x = static_cast<float>(distX(gen));
    float y = static_cast<float>(distY(gen));

    rain.push_back(Rain({x, y}));
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "rain");

    sf::RectangleShape player({40.f, 40.f});
    player.setFillColor(sf::Color::White);
    player.setPosition({375.f, 560.f});
    float speed = 0.08f;

    vector<Rain> rain;
    rainRandomSpawn(rain);

    sf::Clock rainClock;

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (rainClock.getElapsedTime().asSeconds() >= 0.2f) {
            rainRandomSpawn(rain);
            rainClock.restart();
        }
        
        Movement(player, speed);
        window.clear(sf::Color(49, 90, 131));
        window.draw(player);
        for (Rain& drop : rain) {
            drop.draw(window);
            drop.movementRain();
        }
        for (Rain& drop : rain) {
            if (player.getGlobalBounds().findIntersection(drop.getBounds())) {
                player.setPosition({375.f, 275.f});
            }
        }
        window.display();
    }
}
// g++ rain.cpp -o rain.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system
// i need a rest. I've done enough