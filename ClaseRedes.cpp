#include <iostream>
#include <conio.h>
#include <SFML/Network.hpp>

#include "ConsoleControl.h"

void RunClient();
void RunServer();

unsigned short port = 3001;

int main()
{
    std::cout << "Select" << std::endl << "Client -> C" << std::endl << "Server -> S" << std::endl;
 
    char mode = ' ';

    do {

        mode = ConsoleControl::WaithForReadNextChar();

    } while (mode != 'C' && mode != 'c' && mode != 'S' && mode != 's');

    switch (mode){
        case 'C':
        case 'c': 
            RunClient();
            break;

        case 'S':
        case 's':
            RunServer();
            break;
    }

    while (true) {

    }

}

void RunClient() {

    std::cout << "Client";



    /*sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("10.40.2.45", port); //10.40.2.45

    if (status != sf::Socket::Done) {
        std::cout << std::endl << "Error on connect to server";
        return;
    }

    while (true)
    {
        std::cout << std::endl << "Next Message: ";
        std::string message;
        std::getline(std::cin, message);

        char data[100];

        int stringSize = message.length();
        for (int i = 0; i < stringSize; i++) {
            data[i] = message[i];
        }

        if (socket.send(data, 100) != sf::Socket::Done) {
            std::cout << std::endl << "Error sending message";
        }

    }*/

}

void RunServer() {

    std::cout << "Server";

    /*
    sf::TcpListener listener;

    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << std::endl << "Error on start listener";
        return;
    }

    sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
    std::cout << std::endl << "Listening on IP: " + ipAddress.toString();

    sf::TcpSocket client;

    if (listener.accept(client) != sf::Socket::Done) {
        std::cout << std::endl << "Error on accept Client";
        return;
    }

    std::cout << std::endl << "Client Connected" << client.getRemoteAddress().toString();

    while (true) {
        char data[100];
        std::size_t received;

        std::string message;

        if (client.receive(data, 100, received) != sf::Socket::Done) {
            std::cout << std::endl << "Error receiving message";
        }
        else {
            for (size_t i = 0; i < received; i++) {
                message += data[i];
            }

            std::cout << std::endl << message;
        }
    }*/

}