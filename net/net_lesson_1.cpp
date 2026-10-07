#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    // resolve() возвращает std::optional: значение может быть, а может и не быть
    optional<sf::IpAddress> ip = sf::IpAddress::getLocalAddress();

    if (ip.has_value()) {
        cout << ip->toString() << "\n"; // -> достаёт значение из optional
    } else {
        cout << "No ip\n"; 
    }


}
// g++ -std=c++17 net/net_lesson_1.cpp -o net/net_lesson_1.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system