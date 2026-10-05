#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

// enum class GameState {
//     Menu,
//     Playing, 
// }; мороки много

class Snake {
private:
    sf::RectangleShape rectangle;
    vector<sf::Vector2f> bodyPositions;
    sf::Vector2f direction{0.f, 0.f};
    float cell_size = 25.f;
public:
    Snake(sf::Vector2f startPos) : rectangle{sf::Vector2f{25.f, 25.f}}{
        rectangle.setFillColor(sf::Color::Green);
        bodyPositions.push_back(startPos);
        bodyPositions.push_back({startPos.x - cell_size, startPos.y});
        bodyPositions.push_back({startPos.x - cell_size * 2, startPos.y});
    }

    void draw(sf::RenderWindow& window) {
        for (sf::Vector2f pos : bodyPositions) {
            rectangle.setPosition(pos);
            window.draw(rectangle);
        }
    }

    void setDirection(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Key::W) direction = {0.f, -1.f};
        if (key == sf::Keyboard::Key::S) direction = {0.f, 1.f};
        if (key == sf::Keyboard::Key::A) direction = {-1.f, 0.f};
        if (key == sf::Keyboard::Key::D) direction = {1.f, 0.f};
    }
    void movement(float speed) {
        if (direction.x == 0.f && direction.y == 0.f) {
            return; // не двигаемся, пока не задано направление
        }
        for (int i = bodyPositions.size() - 1; i > 0; i--) {
            bodyPositions[i] = bodyPositions[i - 1];
        }

        bodyPositions[0].x += direction.x * cell_size;
        bodyPositions[0].y += direction.y * cell_size;
    } 
    sf::Vector2f getPosition() {
        return bodyPositions[0];
    }
    sf::FloatRect getBounds() {
        return sf::FloatRect({bodyPositions[0].x, bodyPositions[0].y}, {25.f, 25.f});
    }
    void addOne() {
        bodyPositions.push_back(bodyPositions.back());
    }
    bool selfCollision() {  
        for (int i = 1; i < bodyPositions.size(); i++) {
            if (bodyPositions[0] == bodyPositions[i]) {
                return true;
            }
        }
        return false;
    }
};

class Apple {
private:
    sf::CircleShape circle;
public:
    Apple(sf::Vector2f startPos) : circle{15.f} {
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(startPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(circle);
    }

    sf::FloatRect getBounds() { 
        return circle.getGlobalBounds();
    }
};

void randomSpawn(vector<Apple>& apples) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distX(0, 775);
    uniform_int_distribution<int> distY(0, 575);

    float x = static_cast<float>(distX(gen));
    float y = static_cast<float>(distY(gen));

    apples.push_back(Apple({x, y}));
}

// ну что? Ты понял? - нет
int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "snake_body");
    Snake snake({375.f, 275.f});
    vector<Apple> apples;
    randomSpawn(apples);
    float snake_speed = 300.f;
    sf::Clock moveClock;
    const float moveDelay = 0.13f;

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {}

    sf::Text counter(font, "Points: ", 30);
    int score = 0;
    counter.setFillColor(sf::Color::White);
    counter.setPosition({10.f, 10.f}); 

    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                snake.setDirection(key->code);
            }
        }
        window.clear(sf::Color::Black);
        snake.draw(window);

        if (moveClock.getElapsedTime().asSeconds() >= moveDelay) {
            snake.movement(25.f); // cell_size
            moveClock.restart();
        }

        int hits = 0;
        for (int i = 0; i < apples.size(); i++) {
            if (snake.getBounds().findIntersection(apples[i].getBounds())) {
                apples.erase(apples.begin() + i);
                hits++;
                i--; 
                snake.addOne();
            }
        }
        score += hits;
        for (int i = 0; i < hits; i++) {
            randomSpawn(apples);
        }
        for (Apple& apl : apples) {
            apl.draw(window);
        }

        counter.setString("Points: " + to_string(score));
        window.draw(counter);

        // проверки
        sf::Vector2f pos = snake.getPosition();
        if (pos.x < 0.f || pos.y < 0.f || pos.x + 25.f > 800.f || pos.y + 25.f > 600.f) {
            window.close();
        }
        if (snake.selfCollision()) {
            return 0;
        }
        window.display();
    }
}
// stupid asf
// g++ snake.cpp -o snake.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system