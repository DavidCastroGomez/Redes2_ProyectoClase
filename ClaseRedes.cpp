#include <iostream>
#include <conio.h>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "ConsoleControl.h"
#include "Chat.h"

void RunClient();
void RunServer();
void RunWindows();

unsigned short port = 3001;

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

    Chat* chat = Chat::Client(ip, port);
}

void RunServer() {

    std::cout << "Server";

    Chat* chat = Chat::Server(port);

}

void RunWindows() {

    sf::RenderWindow windows;

    windows.create(sf::VideoMode(800, 600), "Chat");
    windows.setFramerateLimit(60);

    sf::Text label;

    sf::Font font;
    font.loadFromFile("Minecraft.ttf");

    label.setFont(font);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);
    label.setString("Hello World");
    label.setOrigin(0.5, 0.5);

    label.setPosition(windows.getSize().x * 0.5, windows.getSize().y * 0.5);

    while (windows.isOpen()) {
        windows.clear(sf::Color::Black);
        windows.draw(label);
        windows.display();
    }

}