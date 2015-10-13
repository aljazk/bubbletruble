#ifndef VERTCIRCLE_H
#define VERTCIRCLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

class VertCircle{
		sf::Vector2f pos;
		float radius;
		sf::Color color;
	public:
		int edges;
		VertCircle();
		VertCircle(const sf::Vector2f, const float);
		void set(const sf::Vector2f, const float);
		void add(sf::VertexArray&);
		
}; 

#endif