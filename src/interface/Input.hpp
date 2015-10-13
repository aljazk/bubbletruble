#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "../draw/VertQuad.hpp"
#include <string>

class Input{
		sf::Vector2f tpos;
		sf::Vector2f tsize;
		sf::Vector2f pos;
		sf::Vector2f size;
		sf::Color color;
		std::string name;
		bool focus;
	public:
		Input();
		Input(const sf::Vector2f);
		Input(const sf::Vector2f, const std::string);
		void setName(const std::string);
		std::string getName();
		void getVert(sf::VertexArray&);
		void getText(sf::Text&);
		void click(const sf::Vector2i);
		void hover(const sf::Vector2i);
		void addChar(const char);
};

#endif