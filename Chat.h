#pragma once
#include <iostream>
#include <mutex>
#include <SFML/Network.hpp>
#include <vector>

class Chat
{
private:

	std::vector<std::string> _messages;
	std::mutex _messageMutex;

	sf::IpAddress _serverAddress;

	Chat() {};

	void ShowMessage(std::string);
	void ShowWarning(std::string);
	void ShowError(std::string);

	void ListenClientConnections(unsigned short port);

public:

	static Chat* Server(unsigned short port);
	static Chat* Client(std::string ip, unsigned short port);

};

