#include "TcpSocket.h"

bool TcpSocket::Connect(std::string ip, unsigned short port)
{
	return connect(ip,port) == sf::Socket::Done;
}

void TcpSocket::Receive()
{
	Packet packet;

	sf:Socket::Status status = receive(packet);

	switch (status)
	{
	case sf::Socket::Done:
		ProcessPacket(packet);
		break;
	case sf::Socket::Disconnected:
		_onSocketDisconnectMutex.lock();

		for (OnSocketDisconnect onDisconect : _onSocketDisconnectList) {
			onDisconect(this);
		}
		_onSocketDisconnectList.clear();
		_onSocketDisconnectMutex.unlock();
		break;

	case sf::Socket::NotReady:
	case sf::Socket::Partial:
	case sf::Socket::Error:
	default:
		//TODO Deberes gestionar
		break;
	}
}

bool TcpSocket::Send(Packet::PacketKey key)
{
	Packet signedPacket;
	signedPacket << key;

	return send(signedPacket) == sf::Socket::Done;
}

bool TcpSocket::Send(Packet::PacketKey key, Packet packet)
{
	Packet signedPacket;
	signedPacket << key;

	signedPacket.append(packet.getData(), packet.getDataSize());

	return send(signedPacket) == sf::Socket::Done;
}

void TcpSocket::Subscribe(Packet::PacketKey key, OnRecievePacket onRecievePacket)
{
	_subscriptionsMutex.lock();
	_subscriptions[key] = onRecievePacket; //TODO deberes multiples subs de 1 key
	_subscriptionsMutex.unlock();
}

void TcpSocket::SubscribeAsync(Packet::PacketKey key, OnRecievePacket onRecievePacket)
{
	std::thread* subscribeThread = new std::thread(&TcpSocket::Subscribe, this, key, onRecievePacket);
	subscribeThread->detach();
}

void TcpSocket::SubscribeOnDisconnect(OnSocketDisconnect onSocketDisconnect)
{
	_onSocketDisconnectMutex.lock();
	_onSocketDisconnectList.push_back(onSocketDisconnect);
	_onSocketDisconnectMutex.unlock();
}

void TcpSocket::ProcessPacket(Packet packet)
{
	Packet::PacketKey key;
	packet >> key;

	std::map<Packet::PacketKey, OnRecievePacket>::iterator it;

	_subscriptionsMutex.lock();

	it = _subscriptions.find(key);
	if (it != _subscriptions.end()) {
		it->second(packet);
	}

	_subscriptionsMutex.unlock();
}
