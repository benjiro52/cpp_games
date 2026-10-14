#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::TcpListener listener;
    sf::TcpSocket client;

    if (listener.listen(53000) != sf::Socket::Status::Done) { // слушает порт
        cout << "no port found\n";
        return 1; 
    }
    
    cout << "waiting for client...\n";

    if (listener.accept(client) != sf::Socket::Status::Done) {
        cout << "Problem accept\n";
        return 1;
    }

    optional<sf::IpAddress> client_ip = client.getRemoteAddress();
    if (client_ip.has_value()) {
        cout << "Client connected: " << client_ip->toString() << ":" << client.getRemotePort() << "\n";
    } else {
        cout << "Could not get client address\n";
    }

    sf::Packet packet;
    string nick, text;

    for (int i = 0; i < 100; i++) {
        packet.clear();
        if (client.receive(packet) != sf::Socket::Status::Done) { // socket.receive(буфер, размер_буфера, received)
            cout << "Receive failed\n";
            return 1;
        }
        if (!(packet >> nick >> text)) {
            cout << "Bad packet\n";
            return 1;
        }

        cout << "[" << nick << "]: " << text << "\n";
    }

    cin.get();
} 
// g++ -std=c++17 net/server.cpp -o net/server.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system