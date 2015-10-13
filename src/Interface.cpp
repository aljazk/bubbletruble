#include "Interface.hpp"

Interface::Interface(){
	texture.loadFromFile("images/button.png");
	font.loadFromFile("arial.ttf");
	buttons.push_back(Button(sf::Vector2f(100,100), "Host", 1));
	buttons.push_back(Button(sf::Vector2f(400,100), "Client", 2));
	inputs.push_back(Input(sf::Vector2f(400,210), "localhost"));
}

int Interface::check(sf::RenderWindow &window){
	mouse = sf::Mouse::getPosition(window);
	for(unsigned int i=0; i<buttons.size(); i++){
		buttons[i].hover(mouse);
	}
	for(unsigned int i=0; i<inputs.size(); i++){
		inputs[i].hover(mouse);
	}
	int action = 0;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(!mouseDowns){
			for(unsigned int i=0; i<buttons.size(); i++){
				if (buttons[i].click(mouse)){
					action = buttons[i].action;
				}
			}
			for(unsigned int i=0; i<inputs.size(); i++){
				inputs[i].click(mouse);
			}
		}
		mouseDowns = true;
	} else {
		mouseDowns = false;
	}
	
	return action;
}

void Interface::enterText(sf::Event event){
	if (event.type == sf::Event::TextEntered){
		for(unsigned int i=0; i<inputs.size(); i++){
			if (event.text.unicode < 128){
				inputs[i].addChar(event.text.unicode);
			}
		}
	}
}

void Interface::draw(sf::RenderWindow &window){
	sf::VertexArray objects;
	objects.setPrimitiveType(sf::Quads);
	
	for(unsigned int i=0; i<buttons.size(); i++){
		buttons[i].getVert(objects);
	}
	for(unsigned int i=0; i<inputs.size(); i++){
		inputs[i].getVert(objects);
	}
	window.draw(objects, &texture);
	
	sf::Text text;
	text.setFont(font);
	for(unsigned int i=0; i<buttons.size(); i++){
		buttons[i].getText(text);
		window.draw(text);
	}
	for(unsigned int i=0; i<inputs.size(); i++){
		inputs[i].getText(text);
		window.draw(text);
	}
}

std::string Interface::getName(const unsigned int id){
	return inputs[id].getName();
}