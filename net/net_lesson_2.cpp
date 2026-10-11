#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::TcpListener listener;

    // listen(порт) возвращает sf::Socket::Status
    if (listener.listen(53000) != sf::Socket::Status::Done) {
        cout << "no port found\n";
        return 1; // что-то пошло не так
    }

    cout << "waiting for client...\n";
    
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Status::Done) {
        cout << "Problem accept\n";
        return 1; // что-то пошло не так
    }

    optional<sf::IpAddress> client_ip = client.getRemoteAddress();
    if (client_ip.has_value()) {
        cout << "Client connected: " << client_ip->toString() << ":" << client.getRemotePort() << "\n";
    } else {
        cout << "Could not get client address\n";
    }
} 
// g++ -std=c++17 net/net_lesson_2.cpp -o net/net_lesson_2.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system