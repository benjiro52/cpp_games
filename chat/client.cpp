#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::TcpSocket client_socket; 

    // проверка на ip
    auto serverIp = sf::IpAddress::resolve("ip");
    if (!serverIp) {
        cout << "Bad IP\n";
        return 1;
    }

    // подключается к порту 53000 
    if (client_socket.connect(*serverIp, 53000) != sf::Socket::Status::Done) { 
        cout << "Could not connect\n";
        cin.get();
        return 1;
    } else {
        cout << "Connected to server!\n";
    }

    sf::Packet packet;
    string nick, text;
    cout << "Nick: ";
    getline(cin, nick);

    // отправка пакетика(100)
    for (int i = 0; i < 100; i++) {
        cout << "Message: ";
        getline(cin, text);

        packet.clear();
        packet << nick << text; // сам пакетик
        if (client_socket.send(packet) != sf::Socket::Status::Done) {
            cout << "Send failed\n";
            return 1;
        }
    }


    cin.get();
}
// g++ -std=c++17 chat/client.cpp -o chat/client.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system