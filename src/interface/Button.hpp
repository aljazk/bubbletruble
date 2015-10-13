#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "../draw/VertQuad.hpp"
#include <string>

class Button{
		sf::Vector2f tpos;
		sf::Vector2f tsize;
		sf::Vector2f pos;
		sf::Vector2f size;
		sf::Color color;
		std::string name;
	public:
		int action;
		Button();
		Button(const sf::Vector2f);
		Button(const sf::Vector2f, const std::string);
		Button(const sf::Vector2f, const std::string, const int);
		void setName(const std::string);
		void getVert(sf::VertexArray&);
		void getText(sf::Text&);
		bool click(const sf::Vector2i);
		void hover(const sf::Vector2i);
};

#endif