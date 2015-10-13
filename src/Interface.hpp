#ifndef INTERFACE_H
#define INTERFACE_H

#include "interface/Button.hpp"
#include "interface/Input.hpp"
#include <iostream>
#include <vector>

class Interface{
		sf::Texture texture;
		sf::Font font;
		std::vector<Button> buttons;
		std::vector<Input> inputs;
		sf::Vector2i mouse;
		bool mouseDowns;
	public:
		Interface();
		int check(sf::RenderWindow&);
		void draw(sf::RenderWindow&);
		void enterText(sf::Event);
		std::string getName(const unsigned int);
};

#endif