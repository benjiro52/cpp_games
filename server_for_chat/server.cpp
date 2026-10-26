#include <SFML/Network.hpp>
#include <bits/stdc++.h>
using namespace std;

int main() {
    sf::TcpListener listener;
    sf::SocketSelector selector;
    vector<unique_ptr<sf::TcpSocket>> clients; 

    if (listener.listen(53000) != sf::Socket::Status::Done) { // слушает порт
        cout << "no port found\n";
        return 1; 
    }

    sf::Packet packet;
    string nick, text;

    selector.add(listener);
    while (true) {
        if (!selector.wait()) continue;   // ждём событие
        
        if (selector.isReady(listener)) {
            auto new_client = make_unique<sf::TcpSocket>();

            if (listener.accept(*new_client) == sf::Socket::Status::Done) {
                optional<sf::IpAddress> client_ip = new_client->getRemoteAddress();
                if (client_ip.has_value()) {
                    cout << "New client connected: " << client_ip->toString() << ":" << new_client->getRemotePort() << "\n";
                }
                selector.add(*new_client);
                clients.push_back(move(new_client)); 
                cout << "Client joined, total: " << clients.size() << "\n";
            } else {
                cout << "Failed to accept new client\n";
            }
        }
        for (auto& client : clients) {
            if (selector.isReady(*client)) {
                packet.clear();
                auto status = client->receive(packet);
                if (status == sf::Socket::Status::Done) {
                    if (!(packet >> nick >> text)) {
                        cout << "Bad packet\n";
                        continue;
                    }
                    cout << "[" << nick << "]: " << text << "\n";
                    for (auto& other : clients) { // рассылка
                        if (other.get() != client.get()) {
                            if (other->send(packet) != sf::Socket::Status::Done) {
                                cout << "Send to client failed\n";
                            }
                        }
                    }
                } else if (status == sf::Socket::Status::Disconnected) {
                    cout << "Client disconnected" << "\n";
                    selector.remove(*client);
                } else {
                    cout << "Receive failed\n";
                }                
            }
        }
        

    }
    // i dont understand anything
    // stupid asf 
} 
// g++ -std=c++17 sever_for_chat/server.cpp -o server_for_chat/server.exe -IC:/msys64/ucrt64/include -LC:/msys64/ucrt64/lib -lsfml-network -lsfml-system