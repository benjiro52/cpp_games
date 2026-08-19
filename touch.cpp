#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class redRectangle {
private:
    sf::RectangleShape red_rectangle;
public:
    redRectangle(sf::Vector2f startPos) : red_rectangle({25.f, 25.f}) {
        red_rectangle.setFillColor(sf::Color::Red);
        red_rectangle.setPosition(startPos);
    }

    sf::FloatRect getBounds() {
        return red_rectangle.getGlobalBounds();
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(red_rectangle);
    }
};

void Movement(sf::RectangleShape& player, float speed) {
    sf::Vector2f pos = player.getPosition();
    pos.x;
    pos.y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        if (player.getPosition().y - speed >= 0.f) {
            player.move({0.f, -speed});    
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if (player.getPosition().y + 20.f + speed <= 600.f) {
            player.move({0.f, speed});
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (player.getPosition().x - speed >= 0.f) {
            player.move({-speed, 0.f});
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (player.getPosition().x + 20.f + speed <= 800.f) {
            player.move({speed, 0.f});
        }
    }
}

void spawnRedRectangles(vector<redRectangle>& obstacles) {
    obstacles.push_back(redRectangle({50.f, 50.f}));
    obstacles.push_back(redRectangle({150.f, 80.f}));
    obstacles.push_back(redRectangle({250.f, 120.f}));
    obstacles.push_back(redRectangle({350.f, 60.f}));
    obstacles.push_back(redRectangle({450.f, 200.f}));
    obstacles.push_back(redRectangle({550.f, 150.f}));
    obstacles.push_back(redRectangle({650.f, 400.f}));
    obstacles.push_back(redRectangle({700.f, 500.f}));
    obstacles.push_back(redRectangle({200.f, 450.f}));
    obstacles.push_back(redRectangle({400.f, 350.f}));
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800,600}), "touch");

    sf::RectangleShape player({25.f, 25.f});
    player.setFillColor(sf::Color::White);
    player.setPosition({375.f, 275.f});

    float speed = 0.1f;
    vector<redRectangle> obstacles;
    spawnRedRectangles(obstacles);


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        Movement(player, speed);

        window.clear(sf::Color::Black);
        window.draw(player);
        for (redRectangle& obstacle : obstacles) {
            obstacle.draw(window);
        }
        for (redRectangle& obstacle : obstacles) {
            if (player.getGlobalBounds().findIntersection(obstacle.getBounds())) {
                player.setPosition({375.f, 275.f});
            }
        }
        window.display();
    }
    return 0;
}

// g++ touch.cpp -o touch.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system