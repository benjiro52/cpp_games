#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Obstacle {
private:
    sf::CircleShape circle;
public:
    Obstacle(sf::Vector2f startPos) : circle{28.f} {
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(circle);
    }

    void move_obstacle(float speed, float deltaTime) {
        float distance = speed * deltaTime;
        circle.move({0.f, distance});
    }   

    sf::FloatRect getBounds() { // for touching
        return circle.getGlobalBounds();
    } 
};

void randomSpawn(vector<Obstacle>& obstacles) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distX(0, 760);
    uniform_int_distribution<int> distY(0, 10);

    float x = static_cast<float>(distX(gen));
    float y = static_cast<float>(distY(gen));

    obstacles.push_back(Obstacle({x, y}));
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "aim");
    vector<Obstacle> obstacles;
    float speed = 450.f;
    int clicks = 0;

    sf::Clock deltaClock;
    sf::Clock clock;

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) { 

    }
    sf::Text counter(font, "Points: ", 30);
    counter.setFillColor(sf::Color::White);
    counter.setPosition({10.f, 10.f});

    while(window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    sf::Vector2f clickPos = window.mapPixelToCoords(mouse->position);
                    for (int i = 0; i < obstacles.size(); i++) {
                        if (obstacles[i].getBounds().contains(clickPos)) {
                            obstacles.erase(obstacles.begin() + i);
                            clicks++;
                            counter.setString("Points: " + to_string(clicks));
                            break;
                        }
                    }
                }
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();
        window.clear(sf::Color::Black);
        window.draw(counter);
        if (clock.getElapsedTime().asSeconds() >= 0.2f) {
            randomSpawn(obstacles);
            clock.restart();
        }
        for (Obstacle& i : obstacles) {
            i.draw(window);
            i.move_obstacle(speed, deltaTime);
        }
        window.display();
    }
}
// g++ aim.cpp -o aim.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system