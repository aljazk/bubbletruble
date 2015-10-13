#ifndef HOST_H
#define HOST_H

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

class Host{
		sf::TcpListener listener;
		unsigned int port;
		sf::TcpSocket client;
	public:
		Host();
		Host(const unsigned int);
		void create();
		void acceptClient();
		sf::Packet receive();
		void send(sf::Packet);
};

#endif