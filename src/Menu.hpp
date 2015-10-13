#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Interface.hpp"
#include "Bubble.hpp"
#include "Player.hpp"
#include "Host.hpp"
#include "Client.hpp"
#include <iostream>
#include <sstream>

using namespace std;

class Menu
{
    public:
		Menu();
    private:
		Interface inter;
		sf::Texture back;
		sf::Vector2u backSize;
		void mainMenu();
		void gameMenu(int);
		void pauseMenu();
		sf::RenderWindow window;
		int windowX, windowY;
		sf::Font font;
		sf::Text text;
		sf::Clock clock;
		float eclipsed;
		bool mouseDown;
};

#endif
