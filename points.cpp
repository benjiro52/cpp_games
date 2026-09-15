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

    void Movement(float speed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (rectangle.getPosition().y - speed >= 0.f) {
                rectangle.move({0.f, -speed});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (rectangle.getPosition().y + 25.f + speed <= 600.f) {
                rectangle.move({0.f, speed});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (rectangle.getPosition().x - speed >= 0.f) {
                rectangle.move({-speed, 0.f});
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (rectangle.getPosition().x + 25.f + speed <= 800.f) {
                rectangle.move({speed, 0.f});
            }
        }
    }

    sf::FloatRect getBounds() {
        return rectangle.getGlobalBounds();
    }
};

class Obstacle {
private:
    sf::CircleShape obstacle;
public:
    Obstacle (sf::Vector2f startPos) : obstacle{20.f} {
        obstacle.setFillColor(sf::Color(128, 128, 128));
        obstacle.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(obstacle);
    }

    sf::FloatRect getBounds() {
        return obstacle.getGlobalBounds();
    }

};

void spawnObstacle(vector<Obstacle>& obstacles_vec) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distX(0, 775); // 800 - 25
    uniform_int_distribution<int> distY(0, 575); // 600 - 25

    float x = static_cast<float>(distX(gen));
    float y = static_cast<float>(distY(gen));

    obstacles_vec.push_back(Obstacle({x, y}));
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "preparing1");
    GameState currentState = GameState::Menu;

    Player player({375.f, 275.f});
    float player_speed = 0.05f;

    vector<Obstacle> obstacles_vec;
    for (int i = 0; i < 1; i++) {
        spawnObstacle(obstacles_vec);
    }

    // text
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        // обработка ошибки, если файл не найден
    }
    sf::Text text(font, "Welcome to preparing1. Press Enter to continue", 30);
    text.setFillColor(sf::Color::White);
    text.setPosition({50.f, 250.f});

    // counter
    int score = 0;
    sf::Text counter(font, "Points: 0", 15);
    counter.setFillColor(sf::Color::White);
    counter.setPosition({10.f, 10.f});


    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        
        if (currentState == GameState::Menu) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                currentState = GameState::Playing;
            }
        }
        if (currentState == GameState::Menu) {
            window.clear(sf::Color::Black);
            window.draw(text);
        }
        if (currentState == GameState::Playing) {
            window.clear(sf::Color::Black);
            player.Movement(player_speed);
            player.draw(window);

            int hits = 0;
            for (int i = 0; i < obstacles_vec.size(); i++) {
                if (player.getBounds().findIntersection(obstacles_vec[i].getBounds())) {
                    obstacles_vec.erase(obstacles_vec.begin() + i);
                    hits++;
                    i--; 
                }
            }

            score += hits;
            for (int i = 0; i < hits; i++) {
                spawnObstacle(obstacles_vec);
            }
            for (Obstacle& obs : obstacles_vec) {
                obs.draw(window);
            }

            counter.setString("Points: " + to_string(score));
            window.draw(counter);

            // finish spawnObstacle
        }
        window.display();
    }
}
// g++ points.cpp -o points.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system