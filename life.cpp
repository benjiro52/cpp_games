#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

class Life_table {
private: 
    sf::RectangleShape rectangle;
public:

};

// sf::Vertex - это точка с двумя основными свойствами: позиция (x, y) и цвет
// пример: sf::Vertex v({100.f, 50.f}, sf::Color::Red);
void print_grid(sf::RenderWindow& window, vector<vector<int>>& grid, int cell) {
    sf::VertexArray triangles(sf::PrimitiveType::Triangles);

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == 1) {
                float px = x * cell;
                float py = y * cell;

                sf::Vector2f A(px, py);
                sf::Vector2f B(px + cell, py);
                sf::Vector2f C(px + cell, py + cell);
                sf::Vector2f D(px, py + cell);

                // первый треугольник
                triangles.append(sf::Vertex(A, sf::Color::Green)); // добавить вершину
                triangles.append(sf::Vertex(B, sf::Color::Green));
                triangles.append(sf::Vertex(C, sf::Color::Green));

                // второй треугольник
                triangles.append(sf::Vertex(A, sf::Color::Green));
                triangles.append(sf::Vertex(C, sf::Color::Green));
                triangles.append(sf::Vertex(D, sf::Color::Green));


            }
        }
    }
    window.draw(triangles);
}

int main() {
    const int cols = 80;
    const int rows = 60;
    const int cell = 10;
    vector<vector<int>> grid(rows, vector<int>(cols, 0)); // 60 строк 80 рядов
    grid[40][35] = 1; grid[50][20] = 1; // test


    sf::RenderWindow window(sf::VideoMode({800, 600}), "Life");
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        print_grid(window, grid, cell);

        window.display();
    }
}
// am i stupid this time????
// g++ life.cpp -o life.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-graphics -lsfml-window -lsfml-system