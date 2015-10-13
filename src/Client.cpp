#include "Client.hpp"

Client::Client(){
	port = 53000;
	ip = sf::IpAddress("localhost");
}

Client::Client(const unsigned int newPort){
	port = newPort;
	ip = sf::IpAddress("localhost");
}

Client::Client(const char *newIp){
	port = 53000;
	ip = sf::IpAddress(newIp);
}

Client::Client(const std::string &newIp){
	port = 53000;
	ip = sf::IpAddress(newIp);
}

Client::Client(const unsigned int newPort, const std::string newIp){
	port = newPort;
	ip = sf::IpAddress(newIp);
}

void Client::connect(){
	socket.connect(ip, port);
}

sf::Packet Client::receive(){
	sf::Packet packet;
	if (socket.receive(packet) != sf::Socket::Done){
		std::cout << "Error with reciving data | Error " << sf::Socket::Error << std::endl;
		if (sf::Socket::Error == 3){
			connect();
		}
	}
	return packet;
}

void Client::send(sf::Packet packet){
	if (socket.send(packet) != sf::Socket::Done){
		std::cout << "Cannot send data | Error " << sf::Socket::Error << std::endl;
	}
}
