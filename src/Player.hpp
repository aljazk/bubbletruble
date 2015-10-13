#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Network\Packet.hpp>
#include "draw/VertQuad.hpp"
#include <vector>
#include <iostream>

class Player{
		int id;
		sf::Texture texture;
		sf::Texture texture2;
		sf::Vector2f pos;
		vector< sf::Vector3f > pops;
		int vel;
		sf::Vector2f vine;
	public:
		Player();
		Player(int);
		void draw(sf::RenderWindow &);
		void draw(sf::RenderWindow &, sf::Vector3f);
		void draw(sf::RenderWindow &, sf::Packet &);
		void set(sf::Packet &);
		void move(const float);
		void move1(const float);
		void stopVine();
		vector<sf::Vector3f> getPops();
		void getPops(sf::Packet&);
		sf::Vector3f getPos();
		void getPos(sf::Packet&);
};

#endif