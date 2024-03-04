#include <iostream>
#include <conio.h>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "ConsoleControl.h"
#include "Chat.h"
#include "ConnectionAbstraction/SocketsManager.h"
#include "WindowsHelpers/Window.h"

void RunClient();
void RunServer();
void RunWindows();

unsigned short port = 3001;

enum PackagesIds: Packet::PacketKey {Message = 0};

int main()
{
    std::cout << "Select" << std::endl << "Client -> C" << std::endl << "Server -> S" << std::endl;
 
    char mode = ' ';

    RunWindows();

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

    std::cout << std::endl << "Set server IP -->";

    std::string ip;
    std::getline(std::cin, ip);

    //Chat* chat = Chat::Client(ip, port);

    SocketsManager* SM = new SocketsManager([](TcpSocket* socket)
        {
            std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();

            socket->Subscribe(Message, [socket](Packet packet)
                {
                    std::string message;
                    packet >> message;
                    std::cout << std::endl << "Message: " << message;
                });

            socket->SubscribeOnDisconnect([](TcpSocket* socket) {
                std::cout << std::endl << "Socket disconnected: " << socket->getRemoteAddress().toString();
                });


            std::string response = "I am a client";
            Packet packet;
            packet << response;

            socket->Send(Message, packet);
        });


    if (SM->ConnectToServer(ip, port)) {
        SM->StartLoop();
    }

}

void RunServer() {

    std::cout << "Server";

    //Chat* chat = Chat::Server(port);

    SocketsManager* SM = new SocketsManager([](TcpSocket* socket)
        {
            std::cout << std::endl << "Socket connected: " << socket->getRemoteAddress().toString();
            socket->Subscribe(Message, [socket](Packet packet)
                {
                    std::string message;
                    packet >> message;
                    std::cout << std::endl << "Message: " << message;

                    std::string response = "I am the server";
                    Packet responsePacket;
                    responsePacket << response;

                    socket->Send(Message, responsePacket);
                });

            socket->SubscribeOnDisconnect([](TcpSocket* socket) {
                std::cout << std::endl << "Socket disconnected: " << socket->getRemoteAddress().toString();
             });
        });


    if (SM->StartListener(port)) {
        sf::IpAddress ipAddress = sf::IpAddress::getLocalAddress();
        std::cout << "Listening on IP: " << ipAddress.toString();
        SM->StartLoop();
    }


}

void RunWindows() {

    Window window;

    Button* bt = new Button(50, 20, "Pieces/QG.png");
    bt->onClick = []() {
        std::cout << std::endl << "No soy la reina";
        };

    window.AddButton(bt);
    window.RunWindowsLoop();

}