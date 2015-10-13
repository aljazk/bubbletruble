#ifndef BUBBLE_H
#define BUBBLE_H

#define SIZE (10)

#include <SFML\Network\Packet.hpp>
#include "draw/VertCircle.hpp"
#include "draw/VertQuad.hpp"
#include <vector>
#include <iostream>

class Bubble{
        sf::Texture texture;
		vector<int> size;
		vector<sf::Vector2f> pos;
		vector<sf::Vector2f> vel;
		vector<sf::Vector3f> pops;
		int seed;
	public:
		Bubble();
		Bubble(const sf::Vector2f, const sf::Vector2f, const int);
		void draw(sf::RenderWindow &);
		void draw(sf::RenderWindow &, vector<sf::Vector3f>);
		void draw(sf::RenderWindow &, sf::Packet &);
		void set(sf::Packet&);
		void move(const float);
		void create(const sf::Vector2f, const sf::Vector2f, const int);
		void remove();
		void remove(const unsigned int);
		void pop(const unsigned int);
		vector<sf::Vector2i> popAll();
		void addPop(const sf::Vector3f);
		void addPops(const vector<sf::Vector3f>);
		void addPops(sf::Packet&);
		vector<sf::Vector3f> getBubbles();
		void getBubbles(sf::Packet&);
};

#endif