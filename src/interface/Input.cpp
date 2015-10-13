#include "Input.hpp"

Input::Input(){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = sf::Vector2f(100,100);
	size = sf::Vector2f(200,40);
	color = sf::Color(100,100,100,255);
	name = "Input";
	focus = false;
}

Input::Input(const sf::Vector2f newPos){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = newPos;
	size = sf::Vector2f(200,40);
	color = sf::Color(100,100,100,255);
	name = "Input";
	focus = false;
}

Input::Input(const sf::Vector2f newPos, const std::string newName){
	tpos = sf::Vector2f(0,0);
	tsize = sf::Vector2f(0,0);
	pos = newPos;
	size = sf::Vector2f(200,40);
	color = sf::Color(100,100,100,255);
	name = newName;
	focus = false;
}

void Input::setName(const std::string newName){
	name = newName;
}

std::string Input::getName(){
	return name;
}

void Input::getVert(sf::VertexArray &vert){
	VertQuad quad(tpos, tsize, pos, size);
	quad.setCenter(sf::Vector2f(size.x,0));
	quad.setColor(color);
	quad.add(vert);
}

void Input::getText(sf::Text &text){
	text.setString(name);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
	text.setPosition(pos.x+5,pos.y+5);
}

void Input::hover(const sf::Vector2i mouse){
	if(!focus){
		if(mouse.x > pos.x && mouse.x < pos.x+size.x && mouse.y > pos.y && mouse.y < pos.y+size.y){
			color = sf::Color::Blue;
		} else {
			color = sf::Color::White;
		}
	}
}

void Input::click(const sf::Vector2i mouse){
	if(mouse.x > pos.x && mouse.x < pos.x+size.x && mouse.y > pos.y && mouse.y < pos.y+size.y){
		color = sf::Color::Red;
		//name.clear();
		focus = true;
	} else {
		focus = false;
	}
}

void Input::addChar(const char newChar){
	if (focus){
		if (newChar == 8){
			if(name.size() > 0){
				name.erase(name.end()-1, name.end());
			}
		} else {
			name.push_back(newChar);
		}
	}
}