#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::TcpSocket client_socket;
    client_socket.connect(sf::IpAddress::LocalHost, 53000);

    if (client_socket.connect(sf::IpAddress::LocalHost, 53000) != sf::Socket::Status::Done) {
        cout << "Could not connect\n";
        return 1;
    } else {
        cout << "Connected to server!\n";
    }

    string text;
    getline(cin, text);
    
    if (client_socket.send(text.c_str(), text.size()) != sf::Socket::Status::Done) {  // socket.send(данные, размер)
        cout << "Send failed\n";
        return 1;
    }

    cin.get();  
}
// g++ -std=c++17 net/client.cpp -o net/client.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system