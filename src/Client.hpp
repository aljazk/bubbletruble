#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

class Client{
		sf::Socket::Status status;
		unsigned int port;
		sf::TcpSocket socket;
		sf::IpAddress ip;
	public:
		Client();
		Client(const unsigned int);
		Client(const char*);
		Client(const std::string&);
		Client(const unsigned int, const std::string);
		void connect();
		sf::Packet receive();
		void send(sf::Packet);
};

#endif