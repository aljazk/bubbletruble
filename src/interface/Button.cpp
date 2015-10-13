#include "Button.hpp"

Button::Button(){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = sf::Vector2f(100,100);
	size = sf::Vector2f(200,100);
	color = sf::Color(100,100,100,255);
	action = 0;
	name = "Button";
}

Button::Button(const sf::Vector2f newPos){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = newPos;
	size = sf::Vector2f(200,100);
	color = sf::Color(100,100,100,255);
	action = 0;
	name = "Button";
}

Button::Button(const sf::Vector2f newPos, const std::string newName){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = newPos;
	size = sf::Vector2f(200,100);
	color = sf::Color(100,100,100,255);
	action = 0;
	name = newName;
}

Button::Button(const sf::Vector2f newPos, const std::string newName, const int newAction){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = newPos;
	size = sf::Vector2f(200,100);
	color = sf::Color(100,100,100,255);
	action = newAction;
	name = newName;
}

void Button::setName(const std::string newName){
	name = newName;
}

void Button::getVert(sf::VertexArray &vert){
	VertQuad quad(tpos, tsize, pos, size);
	quad.setCenter(sf::Vector2f(size.x,0));
	quad.setColor(color);
	quad.add(vert);
}

void Button::getText(sf::Text &text){
	text.setString(name);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
	text.setPosition(pos.x+5,pos.y+5);
}

void Button::hover(const sf::Vector2i mouse){
	if(mouse.x > pos.x && mouse.x < pos.x+size.x && mouse.y > pos.y && mouse.y < pos.y+size.y){
		color = sf::Color::Blue;
	} else {
		color = sf::Color::White;
	}
}

bool Button::click(const sf::Vector2i mouse){
	if(mouse.x > pos.x && mouse.x < pos.x+size.x && mouse.y > pos.y && mouse.y < pos.y+size.y){
		color = sf::Color::Red;
		return 1;
	}
	return 0;
}