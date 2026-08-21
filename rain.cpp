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

void rainSpawn(vector<Rain>& rain) {
    rain.push_back(Rain({25.f, 25.f}));
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "rain");

    sf::RectangleShape player({40.f, 40.f});
    player.setFillColor(sf::Color::White);
    player.setPosition({375.f, 560.f});
    float speed = 0.08f;

    vector<Rain> rain;
    rainSpawn(rain);

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        Movement(player, speed);
        window.clear(sf::Color(49, 90, 131));
        window.draw(player);
        for (Rain& drop : rain) {
            drop.draw(window);
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