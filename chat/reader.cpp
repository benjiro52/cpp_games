#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::TcpSocket reader_socket; 
    sf::Packet packet;
    string nick, text;
    auto serverIp = sf::IpAddress::resolve("ip");
    
    if (!serverIp) {
        cout << "Bad IP\n";
        return 1;
    }

    if (reader_socket.connect(*serverIp, 53000) != sf::Socket::Status::Done) {
        cout << "Could not connect\n";
        cin.get();
        return 1;
    } else {
        cout << "Connected to server\n";
    }

    while(true) {
        packet.clear();
        if (reader_socket.receive(packet) == sf::Socket::Status::Done) {
            if (!(packet >> nick >> text)) {
                cout << "Bad packet\n";
                continue;
            }
            cout << "[" << nick << "]: " << text << "\n";

        } else {
            cout << "no message found\n";
            break;
        }
    }
}
//  g++ -std=c++17 chat/reader.cpp -o chat/reader.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system