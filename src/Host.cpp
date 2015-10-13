#include "Host.hpp"

Host::Host(){
	port = 53000;
	listener.setBlocking(false);
}

Host::Host(const unsigned int newPort){
	port = newPort;
}

void Host::create(){
	if (listener.listen(port) != sf::Socket::Done){
		std::cout << "Socket couldnt be created at port " << port << std::endl;
	}
}

void Host::acceptClient(){
	if (listener.accept(client) != sf::Socket::Done){
		//std::cout << "No client to accept" << std::endl;
	} else {
		std::cout << "Client found" << std::endl;
	}
}

sf::Packet Host::receive(){
	sf::Packet packet;
	if (client.receive(packet) != sf::Socket::Done){
		if (sf::Socket::Error == 3){
			acceptClient();
		} else {
			std::cout << "Error with reciving data | Error " << sf::Socket::Error << std::endl;
		}
	}
	return packet;
}

void Host::send(sf::Packet packet){
	if (client.send(packet) != sf::Socket::Done){
		std::cout << "Cannot send data | Error " << sf::Socket::Error << std::endl;
	}
}